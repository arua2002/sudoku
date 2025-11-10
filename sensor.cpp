#include "Sensor.h"
#include <Wire.h>
Sensor::Sensor() {
  // Конструктор: можно оставить пустым или добавить инициализацию
}

void Sensor::initCamera() {
  Wire.begin(); // Инициализация шины I2C
  
}