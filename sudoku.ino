#include <ESP32Servo.h>
#include "SudokuSolver.h"
#include "CameraModule.h"
#include <TrackingCamI2C.h>
#include <RobotCar.h>

RobotCar robot;
TrackingCamI2C trackingCam;
SudokuSolver solver;
CameraModule myCAM;
Servo myServo;

const int N = 3;
bool search = false;
bool start = false; 
uint8_t n = 0;
uint8_t tr = 0; 

int initial[N][N] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

// Решаем судоку
void sud(int initial[N][N]) {
  solver.setInitial(initial);
  if (solver.solve()) {
    int solution[N][N];
    solver.getBoard(solution);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        initial[i][j] = solution[i][j];
      }
    }
  } else {
    // Если решения нет, ничего не делаем
  }
}

// Функция задачи для второго ядра
void core2(void *pvParameters) {
  trackingCam.init(51, 400000);
  delay(5000);

  while (true) {
    if (search) {
      n = trackingCam.readBlobs(3); // чтение максимум 3 объектов
    }
    delay(1000); 
  }
}

void setup() {
  Serial.begin(9600);
  myServo.attach(1);

  #if defined(ESP32)
    // Создаем задачу на втором ядре
    xTaskCreatePinnedToCore(
      core2,           // функция задачи
      "Core2Task",     // имя задачи
      10000,           // размер стека
      NULL,            // параметры
      1,               // приоритет
      NULL,            // указатель на задачу
      1                // ядро (1 или 0)
    );
  #endif
}

void ser() { // тут надо будет настроить
  for (int angle = 0; angle <= 90; angle++) {
    myServo.write(angle);
    delay(15);
  }
  for (int angle = 90; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}

void loop() {
  if (tr == 9) {
    sud(initial);
  }

  if (start) {
    // тут так же катает по линии
    ser(); // Хоп-хоп и скинул
    // Здесь добавьте код для движения и логики определения search
    // Например:
    // robot.robotMove(...);
    // В конце:
    // search = !search; // меняет состояние
  }

  // Можно добавить небольшую задержку
  delay(100);
}