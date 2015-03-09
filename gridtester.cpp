// gridtester.cpp - tests class SudokuGrid
// Use AS-IS for CS 24 Project 1
// cmc, 8/26/2014

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "sudokugrid.h"
#include "gridio.h"

// utility functions defined below main:
bool blank(string const &);
bool eq(string, char const *);
string yesno(bool);

int main() {
    SudokuGrid *grid = 0; // pointer, so can test multiple problems

    int row = 0, column = 0, number = 0;
    int problem[9][9];
    string line;

    while ( getline(cin, line) ) {
        if (blank(line)) // skip blank lines
            continue;

        istringstream parser(line);
        string cmnd;
        parser >> cmnd;

        try {
            if (cmnd.at(0) == '#') // skip comments
                ;
            else if (eq(cmnd, "new")) { // read array & create new grid
                cout << "new grid: ";
                if ( getProblem(problem) ) {
                    delete grid; // done with any prior grid
                    grid = 0;
                    grid = new SudokuGrid(problem);
                    cout << endl;
                    display(grid);
                }
                else
                    cout << "missing or bad data in new grid" << endl;
            }
            else if (eq(cmnd, "print")) {
                cout << "current grid:" << endl;
                display(grid);
            }                
            else if (eq(cmnd, "solved?"))
                cout << "grid solved?: " << yesno(grid->isSolved()) << endl;
                    
            else if (!eq(cmnd, "get") && !eq(cmnd, "set")
                  && !eq(cmnd, "row?") && !eq(cmnd, "column?")
                  && !eq(cmnd, "box?") && !eq(cmnd, "cand?"))
                cout << "bad command: " << cmnd << endl;
                
            else { // valid commands that need more data
                // read row index unless command is "column?"
                if (!eq(cmnd, "column?"))
                    parser >> row;
                    if (parser.fail()) {
                        cout << "bad or missing row: " << line << endl;
                        continue;
                    }
                // read column index unless command is "row?"
                if (!eq(cmnd, "row?"))
                    parser >> column;
                    if (parser.fail()) {
                        cout << "bad or missing column: " << line << endl;
                        continue;
                    }
                // read number unless command is "get"
                if (!eq(cmnd, "get"))
                    parser >> number;
                    if (parser.fail()) {
                        cout << "bad or missing number: " << line << endl;
                        continue;
                    }
                    
                // process commands
                if (eq(cmnd, "get")) {
                    cout << "getting number at [" << row << "]["
                    << column << "] - ";
                    number = grid->getNumber(row, column);
                    cout << "got " << number << endl;
                }
                else if (eq(cmnd, "set")) {
                    cout << "setting " << number << " at [" << row << "]["
                    << column << "] - ";
                    grid->setNumber(number, row, column);
                    cout << "done" << endl;
                }
                else if (eq(cmnd, "row?")) {
                    cout << number << " in row " << row << "? ";
                    cout << yesno(grid->occursInRow(number, row)) << endl;
                }
                else if (eq(cmnd, "column?")) {
                    cout << number << " in column " << column << "? ";
                    cout << yesno(grid->occursInColumn(number, column)) << endl;
                }
                else if (eq(cmnd, "box?")) {
                    cout << number << " in box of [" << row << "]["
                         << column << "]? ";
                    cout << yesno(grid->occursInBox(number, row, column)) << endl;
                }
                else if (eq(cmnd, "cand?")) {
                    cout << number << " candidate at [" << row << "]["
                         << column << "]? ";
                    cout << yesno(grid->isCandidate(number, row, column)) << endl;
                }
            }
        }
        catch(const GridException &e) {
            cout << "exception: " << e << endl;
        }
    }
}

// utility returns true if s is all white space
bool blank(string const &s) {
    for (size_t i = 0; i < s.size(); i++) {
        char c = s.at(i);
        if (!isspace(c))
            return false;
    }
    return true;
}
    
// utility simplifies string comparison
bool eq(string s1, char const *s2) {
    for (size_t i = 0; i < s1.size(); i++)
        s1.at(i) = tolower(s1.at(i));
    return s1 == string(s2);
}

// utility returns "yes" if answer is true, or "no" otherwise
string yesno(bool answer) {
    if (answer) return string("yes");
    return string("no");
}
