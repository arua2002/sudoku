# О проекте
## sudoku.ino - основной файл где всё призывается и используется
## RobotCar.h - методы для движения робота 
- Инициализация пинов
  - void preSetup(); - [ ]
- Движение
  - void robotMove(int speedLeft, int speedRight); - [ ]
  - void robotStop(); - [ ]
- Управление моторами
  - void leftMotor(int speed); - [ ]
  - void rightMotor(int speed); - [ ]
- Навигация
  - void goToLine(); - [ ]
  - void goToCross(); - [ ]
  - void goToCube(); - [ ]
  - void turnLeftLine(int time); - [ ]
  - void turnRightLine(int time); - [ ]
  - void forward(int time); - [ ]
- Сенсоры
  - int getSL(); - [ ]
  - int getSR(); - [ ]
  - int getCalibrSL(); - [ ]
  - int getCalibrSR(); - [ ]
  - boolean getCross(); - [ ]
  - boolean getCube(); - [ ]
- Ультразвуковой датчик
  - int uZvuk(); - [ ]
- Тестирование сенсоров
  - void testCalibrSensor(); - [ ]
  - void testSensor(); - [ ]
## SudokuSolver.h
- SudokuSolver();  - [конструктор, заполнение массива нулями]

- установить начальные значения
  - void setInitial(int initial[N][N]);  - [Загружает начальное состояние доски из переданного массива initial]
- решить судоку
  - isSafe(int row, int col, int num)  - [Проверяет, можно ли поставить число num в ячейку [row][col]]
  - findEmptyCell(int &row, int &col)  - [Находит первую свободную (пустую) ячейку (значение 0)]
  - bool solve(); - [запускает решение судоку.]
  - solveSudoku() - [ то рекурсивный метод, использующий алгоритм "backtracking".]
- получить решение
  - void getBoard(int out[N][N]); - [ ]
