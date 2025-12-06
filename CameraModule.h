#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include <Wire.h>
#include "Adafruit_OV7670.h"
#include "Adafruit_ILI9341.h"

class CameraModule {
public:
    CameraModule(
        uint8_t cam_addr,
        uint8_t sda_pin,
        uint8_t scl_pin,
        uint8_t tft_cs,
        uint8_t tft_dc,
        uint8_t tft_mosi,
        uint8_t tft_clk,
        uint8_t tft_miso
    );

    bool begin();
    void captureImage();
    void convertToBlackWhite();
    void displayImage();

private:
    // Объекты камеры и дисплея
    Adafruit_OV7670 cam;
    Adafruit_ILI9341 tft;

    // Буфер изображения
    uint16_t* imageBuffer;
    uint16_t imgWidth;
    uint16_t imgHeight;

    // Внутренние методы
    void initDisplay();
    void initCamera();
};

#endif // CAMERAMODULE_H