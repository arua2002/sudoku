#include "SudokuSolver.h"
#include "CameraModule.h"
#include <TrackingCamI2C.h>

TrackingCamI2C trackingCam;
SudokuSolver solver;
CameraModule myCAM;

const int N = 3;
bool search = false;
uint8_t n = 0;

int initial[N][N] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

// Первая задача (обычная в основном ядре)
void sud(int initial[N][N]) {
  solver.setInitial(initial);
  if (solver.solve()) {
    int solution[N][N];
    solver.getBoard(solution);
    Serial.println("Решение судоку:");
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        Serial.print(solution[i][j]);
        Serial.print(" ");
      }
      Serial.println();
    }
  } else {
    Serial.println("Нет решения.");
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
    delay(1000); // задержка между чтениями
  }
}
void setup() {
  Serial.begin(9600);
  sud(initial);

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

void loop() {
  //добавь здесь код где он ездит и когда останавливается searh делай true и не большая задержка и присваивай N[такой то,такой]=n
}