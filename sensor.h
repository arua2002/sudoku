#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor {
public:
  Sensor();
  void initCamera(); // Метод для инициализации камеры

private:
  // Можно добавить переменные для хранения состояния камеры
};

#endif 