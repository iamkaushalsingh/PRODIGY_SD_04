#include <iostream>
#include <vector>
using namespace std;

// Size of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid
void printGrid(vector<vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in the given position (row, col)
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    // Check if num is not present in current row, current column, and current 3x3 subgrid
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num) return false; // Check row
        if (grid[i][col] == num) return false; // Check column
        if (grid[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) return false; // Check 3x3 subgrid
    }
    return true;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // Find an empty cell (unassigned cell)
    bool found = false;
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                found = true;
                break;
            }
        }
        if (found) break;
    }

    // If no empty cell is found, the Sudoku puzzle is solved
    if (!found) return true;

    // Try numbers 1 to 9 in the current empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Assign number if it's safe

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid)) return true;

            // If assigning num doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be assigned to this cell, backtrack
    return false;
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku puzzle solved:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}