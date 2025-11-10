#include "SudokuSolver.h"

SudokuSolver::SudokuSolver() {
    // заполнение массива нулями
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
}

void SudokuSolver::setInitial(int initial[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = initial[i][j];
        }
    }
}

bool SudokuSolver::isSafe(int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num)
            return false;
        if (board[x][col] == num)
            return false;
    }
    return true;
}

bool SudokuSolver::findEmptyCell(int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0)
                return true;
        }
    }
    return false;
}

bool SudokuSolver::solve() {
    return solveSudoku();
}

bool SudokuSolver::solveSudoku() {
    int row, col;
    if (!findEmptyCell(row, col))
        return true;

    for (int num = 1; num <= 3; num++) {
        if (isSafe(row, col, num)) {
            board[row][col] = num;
            if (solveSudoku())
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

void SudokuSolver::getBoard(int out[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            out[i][j] = board[i][j];
        }
    }
}