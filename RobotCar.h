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
const int IN1 = 12;//13
const int IN2 = 14;//12
const int ENA = 13;//14

const int IN3 = 27;//27
const int IN4 = 26;//26
const int ENB = 25;//25

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
  int getSl = 0;
  int maxl = 10845;
};

#endif
