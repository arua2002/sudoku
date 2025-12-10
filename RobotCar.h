#ifndef ROBOTCAR_H
#define ROBOTCAR_H

#include <Arduino.h>

class RobotCar {
public:
  // Конструктор
  RobotCar();

  // Инициализация пинов
  void preSetup();

  // Движение
  void robotMove(int speedLeft, int speedRight);
  void robotStop();

  // Управление моторами
  void leftMotor(int speed);
  void rightMotor(int speed);

  // Навигация
  void goToLine();
  void goToCross();
  void goToCube();
  void turnLeftLine(int time);
  void turnRightLine(int time);
  void forward(int time);

  // Сенсоры
  int getSL();
  int getSR();
  int getCalibrSL();
  int getCalibrSR();
  boolean getCross();
  boolean getCube();

  // Ультразвуковой датчик
  int uZvuk();

  // Тестирование сенсоров
  void testCalibrSensor();
  void testSensor();

private:
  // Пины
  const int DIR_L1 = 6;
  const int DIR_L2 = 7;
  const int PWM_L = 5;

  const int DIR_R1 = 8;
  const int DIR_R2 = 9;
  const int PWM_R = 10;

  const int PIN_TRIG = 12;
  const int PIN_ECHO = 11;

  const int BLACK = 900;
  const int WHITE = 10;
  const int GREY = 700;
  const int SL_PIN = 1; //A0
  const int SR_PIN = 2;//A2

  int error, v1, v2;
  int k = 3;

  long duration, cm;
  long x, y;
  int minL = 50;
  int minR = 35;
  int maxL = 780;
  int maxR = 550;
};

#endif