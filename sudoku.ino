#include <Arduino.h>
#include "SudokuSolver.h"
#include "Sensor.h"
SudokuSolver solver;
Sensor mySensor;
const int N = 3;
int initia[N][N] = {
    {1, 0, 0},
    {0, 2, 0},
    {0, 0, 3}
  };
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
  mySensor.initCamera();
  sud(initia);

}

void loop() {
  // пусто
}