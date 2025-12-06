# sudoku
// Создание объекта CameraModule с указанием пинов:
// 0x42 — адрес камеры (может отличаться)
// 21 — пин SDA для I2C (камера)
// 22 — пин SCL для I2C (камера)
// 15 — пин CS дисплея
// 2 — пин DC дисплея
// 23 — пин MOSI SPI для дисплея
// 18 — пин CLK SPI для дисплея
// 19 — пин MISO SPI для дисплея
CameraModule camera(
    0x42,       // Адрес камеры
    21,         // SDA (данные I2C для камеры)
    22,         // SCL (тактовый сигнал I2C для камеры)
    15,         // CS (выбор дисплея)
    2,          // DC (поддержка команд дисплея)
    23,         // MOSI (данные SPI для дисплея)
    18,         // CLK (тактовый SPI для дисплея)
    19          // MISO (ответ от дисплея, если нужен)
);
#include "CameraModule.h"

CameraModule camera(0x42, 21, 22, 15, 2, 23, 18, 19);

void setup() {
  Serial.begin(115200);
  if (!camera.begin()) {
    Serial.println("Camera initialization failed");
    while(1);
  }
}

void loop() {
  // Захватить изображение
  camera.captureImage();

  // Обработать изображение в черно-белое
  camera.convertToBlackWhite();

  // Отобразить черно-белое изображение
  camera.displayImage();

  delay(1000);
}