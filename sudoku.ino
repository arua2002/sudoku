#include <Servo.h>
#include "SudokuSolver.h"
#include "CameraModule.h"
#include <TrackingCamI2C.h>

TrackingCamI2C trackingCam;
SudokuSolver solver;
CameraModule myCAM;
Servo myServo;

const int N = 3;
bool search = false;
uint8_t n = 0;
unit8_t tr =0;
int initial[N][N] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

//решаем судоку
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
  }
  else{
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
    delay(1000); // задержка между чтениями
  }
}
void setup() {
  Serial.begin(9600);
  

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
  if(tr = 9){
    sud(initial);
  }
  //добавь здесь код где он ездит и когда останавливается searh делай true и обратно false и не большая задержка и присваивай N[такой то,такой]=n и tr увеличивай
}