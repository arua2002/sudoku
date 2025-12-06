#include "SudokuSolver.h"
#include "Sensor.h"
#include <Dynamixel2Arduino.h>

SudokuSolver solver;
Sensor mySensor;
const int N = 3;
int initia[N][N] = {
    {1, 0, 0},
    {0, 2, 0},
    {0, 0, 3}
};

// Первая задача (обычная в основном ядре)
void sud(int initial[N][N]){
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
void setup() {
  Serial.begin(9600);

  sud(initia);

  // Создаем задачу на втором ядре
  #if defined(ESP32)
    xTaskCreatePinnedToCore(
      core2,          // функция задачи
      "Core2Task",    // имя задачи
      10000,          // размер стека
      NULL,           // параметры
      1,              // приоритет
      NULL,           // указатель на задачу
      1               // номер ядра (1 или 0)
    );
  #endif
}

void loop() {
  // пусто
}
void core2() {
  while (true) {
    // Пустое ядро, ничего не делает
    delay(1000);
  }
}