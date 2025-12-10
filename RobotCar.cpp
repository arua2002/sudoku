#include "RobotCar.h"

RobotCar::RobotCar() {
  // Конструктор оставляем пустым
}

void RobotCar::preSetup() {
  pinMode(DIR_L1, OUTPUT);
  pinMode(DIR_L2, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(DIR_R1, OUTPUT);
  pinMode(DIR_R2, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void RobotCar::leftMotor(int speed) {
  if (speed > 0) {
    digitalWrite(DIR_L1, HIGH);
    digitalWrite(DIR_L2, LOW);
    analogWrite(PWM_L, min(speed, 255));
  } else if (speed < 0) {
    digitalWrite(DIR_L1, LOW);
    digitalWrite(DIR_L2, HIGH);
    analogWrite(PWM_L, min(abs(speed), 255));
  } else {
    digitalWrite(DIR_L1, HIGH);
    digitalWrite(DIR_L2, HIGH);
    analogWrite(PWM_L, 0);
  }
}

void RobotCar::rightMotor(int speed) {
  if (speed > 0) {
    digitalWrite(DIR_R1, LOW);
    digitalWrite(DIR_R2, HIGH);
    analogWrite(PWM_R, min(speed, 255));
  } else if (speed < 0) {
    digitalWrite(DIR_R1, HIGH);
    digitalWrite(DIR_R2, LOW);
    analogWrite(PWM_R, min(abs(speed), 255));
  } else {
    digitalWrite(DIR_R1, HIGH);
    digitalWrite(DIR_R2, HIGH);
    analogWrite(PWM_R, 0);
  }
}

void RobotCar::robotMove(int speedLeft, int speedRight) {
  leftMotor(speedLeft);
  rightMotor(speedRight);
}

void RobotCar::robotStop() {
  robotMove(0, 0);
}

void RobotCar::goToLine() {
  error = getCalibrSR() - getCalibrSL();
  v1 = 150 + (k * error);
  v2 = 150 - (k * error);
  robotMove(v1, v2);
}

boolean RobotCar::getCross() {
  return (getCalibrSR() > BLACK) && (getCalibrSL() > BLACK);
}

void RobotCar::goToCross() {
  while (!getCross()) {
    goToLine();
  }
  robotStop();
}

boolean RobotCar::getCube() {
  return (cm < 10);
}

void RobotCar::goToCube() {
  while (!getCube()) {
    goToLine();
  }
  robotStop();
}

void RobotCar::turnLeftLine(int time) {
  robotMove(-110, 100);
  delay(time);
  while (getCalibrSR() > GREY) {
    robotMove(-60, 50);
  }
}

void RobotCar::forward(int time) {
  robotMove(110, 100);
  delay(time);
}

void RobotCar::turnRightLine(int time) {
  robotMove(110, -100);
  delay(time);
  while (getCalibrSL() > GREY) {
    robotMove(60, -50);
  }
}

int RobotCar::getSL() {
  return analogRead(SL_PIN);
}

int RobotCar::getSR() {
  return analogRead(SR_PIN);
}

int RobotCar::getCalibrSL() {
  x = analogRead(SL_PIN);
  if (x < minL) x = minL;
  if (x > maxL) x = maxL;
  x = (1000 * (x - minL)) / (maxL - minL);
  return x;
}

int RobotCar::getCalibrSR() {
  y = analogRead(SR_PIN);
  if (y < minR) y = minR;
  if (y > maxR) y = maxR;
  y = (1000 * (y - minR)) / (maxR - minR);
  return y;
}

int RobotCar::uZvuk() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);
  cm = duration / 58;
  delay(10);
  return cm;
}

void RobotCar::testCalibrSensor() {
  Serial.print(getCalibrSL());
  Serial.print(' ');
  Serial.println(getCalibrSR());
}

void RobotCar::testSensor() {
  Serial.print(getSL());
  Serial.print(' ');
  Serial.println(getSR());
}