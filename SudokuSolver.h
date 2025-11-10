#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <Arduino.h>

class SudokuSolver {
public:
    static const int N = 3;
    int board[N][N];

    SudokuSolver();

    // установить начальные значения
    void setInitial(int initial[N][N]);

    // решить судоку
    bool solve();

    // получить решение
    void getBoard(int out[N][N]);

private:
    bool isSafe(int row, int col, int num);
    bool findEmptyCell(int &row, int &col);
    bool solveSudoku();
};

#endif