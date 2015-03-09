// gridio.cpp - implements gridio.h functions
// cmc, updated 8/28/2014

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "sudokugrid.h"
#include "gridio.h"

std::ostream &operator<< (std::ostream &out, const GridException &e) {
    switch (e.error) {
        case DATA: return out << "data error";
        case INDEX: return out << "index error";
        case RULE: return out << "Sudoku rule error";
        default: return out; // should never happen
    }
}

GridException::GridException(ErrorType e) : error(e) { }

bool getProblem(int result[9][9]) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            cin >> result[i][j];
            if ( cin.fail() )
                return false;
        }
    return true;
}

void display(SudokuGrid const *grid) {
    cout << "-------------------------" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int number = grid->getNumber(i, j);
            if (number == 0)
                cout << " .";
            else
                cout << " " << number;
            if (j == 2 || j == 5)
                cout << "   ";
        }
        cout << endl;
        if (i == 2 || i == 5)
            cout << endl;
    }
    cout << "-------------------------" << endl;
}
