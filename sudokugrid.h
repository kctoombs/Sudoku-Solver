// sudokugrid.h

// Represents a Sudoku grid - a 9x9 grid of numbers that comprise a single Sudoku
// puzzle. Allows accesses and mutations to the values in this grid, and provides
// several useful utility methods. Does not have methods that solve the puzzle.

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

class SudokuGrid {

public:

    SudokuGrid(const int problem[9][9]);
        // constructor; throws exception if any element of problem <0 or >9

    int getNumber(int row, int column) const;
        // accesses specified element; throws exception if row or column <0 or >8

    void setNumber(int number, int row, int column);
        // sets specified element; throws exception if row or column <0 or >8,
        //     or if number <0 or >9, or if element at that position is fixed

    bool occursInRow(int number, int row) const;
        // true if number occurs in row; throws exception if row <0 or >8

    bool occursInColumn(int number, int column) const;
        // true if number occurs in column; throws exception if column <0 or >8

    bool occursInBox(int number, int row, int column) const;
        // true if number occurs in same 3x3 "box" as specified row and column
        // Note: row and column parameters pertain to the complete 9x9 grid.
        //       There are nine boxes in this grid, where the center box, for
        //       example, spans rows 3-5, columns 3-5.
        // throws exception if row or column <0 or >8

    bool isCandidate(int number, int row, int column) const;
        // true if number is a legal candidate at specified row and column
        // throws exception if row or column <0 or >8

    bool isSolved() const;
        // true if the problem is solved according to the rules of Sudoku:
        //     every row, column and box contains the numbers 1 through 9

private:

    struct SudokuSquare {
        int number;
        bool fixed; // set to true if number cannot be changed
    };

    SudokuSquare array[9][9];
};

#endif
