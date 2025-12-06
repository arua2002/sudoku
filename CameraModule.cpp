#include "CameraModule.h"

// Конструктор
CameraModule::CameraModule(
    uint8_t cam_addr,
    uint8_t sda_pin,
    uint8_t scl_pin,
    uint8_t tft_cs,
    uint8_t tft_dc,
    uint8_t tft_mosi,
    uint8_t tft_clk,
    uint8_t tft_miso
) :
    cam(cam_addr, nullptr, new TwoWire(0)), // инициализация через динамический объект
    tft(tft_clk, tft_miso, tft_mosi, tft_dc, tft_cs)
{
    // Настройка пинов I2C для камеры
    TwoWire* wire = new TwoWire(0);
    wire->begin(sda_pin, scl_pin);
    cam.setWire(wire);
    // Предполагается, что остальные настройки сделаны в begin()
}

// Инициализация
bool CameraModule::begin() {
    // Инициализация дисплея
    initDisplay();

    // Инициализация камеры
    OV7670_status status = cam.begin(CAM_MODE, CAM_SIZE, 30.0);
    if (status != OV7670_STATUS_OK) {
        Serial.println("Camera init failed");
        return false;
    }

    // Чтение регистра PID и VER
    uint8_t pid = cam.readRegister(OV7670_REG_PID);
    uint8_t ver = cam.readRegister(OV7670_REG_VER);
    Serial.print("PID: "); Serial.println(pid, HEX);
    Serial.print("VER: "); Serial.println(ver, HEX);
    return true;
}

void CameraModule::initDisplay() {
    tft.begin(40000000);
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
}

void CameraModule::captureImage() {
    // Центрирование изображения
    tft.endWrite();
    tft.startWrite();
    tft.setAddrWindow((tft.width() - cam.width()) / 2,
                      (tft.height() - cam.height()) / 2,
                      cam.width(), cam.height());

    // Заморозка кадра
    cam.suspend();

    // Конвертация YUV в RGB565, если нужно
    if (CAM_MODE == OV7670_COLOR_YUV) {
        cam.Y2RGB565();
    }

    // Передача буфера на дисплей
    tft.writePixels(cam.getBuffer(), cam.width() * cam.height(), false, true);

    // Продолжение работы камеры
    cam.resume();
}

void CameraModule::convertToBlackWhite() {
    // Предполагается, что у вас есть буфер изображения
    // и вы хотите преобразовать его в черно-белое
    uint16_t* buf = cam.getBuffer(); // Получаем текущий буфер камеры
    imgWidth = cam.width();
    imgHeight = cam.height();

    // Выделение памяти для черно-белого изображения
    // (лучше выделять один раз в конструкторе, если планируете много раз)
    static uint16_t bwBuffer[320*240]; // максимум, лучше динамически выделить

    for (int i = 0; i < imgWidth * imgHeight; i++) {
        uint16_t pixel = buf[i];
        // Распарсим R,G,B из RGB565
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        // Усреднение для черно-белого
        uint8_t gray = (r * 8 + g * 4 + b * 8) / 3;
        // Возвращение в RGB565 (черно-белое)
        uint16_t bw_pixel = ((gray >> 3) & 0x1F) << 11 | ((gray >> 2) & 0x3F) << 5 | ((gray >> 3) & 0x1F);
        bwBuffer[i] = bw_pixel;
    }

    // Можно сохранить в отдельный буфер или заменить текущий
    // Для примера запишем обратно в буфер камеры
    memcpy(cam.getBuffer(), bwBuffer, sizeof(bwBuffer));
}

void CameraModule::displayImage() {
    // Вывод текущего буфера (после обработки)
    tft.endWrite();
    tft.startWrite();
    tft.setAddrWindow((tft.width() - cam.width()) / 2,
                      (tft.height() - cam.height()) / 2,
                      cam.width(), cam.height());
    tft.writePixels(cam.getBuffer(), cam.width() * cam.height(), false, true);
}