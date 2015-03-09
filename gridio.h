// gridio.h
// input-output tools for CS 24 Project 1

#ifndef GRIDIO_H
#define GRIDIO_H

#include "sudokugrid.h"
#include <iosfwd>

enum ErrorType { DATA, INDEX, RULE };

class GridException {
    friend std::ostream &operator<< (std::ostream &, const GridException &);
        // outputs error message of GridException e when '<< e'
public:
    GridException (ErrorType e);
        // creates new GridException - must pass DATA, INDEX or RULE
private:
    ErrorType error;
};

bool getProblem(int[9][9]);
    // fills 9x9 int array parameter from cin
    // returns true if no input errors; false otherwise

void display(SudokuGrid const *);
    // neatly displays the numbers of grid to which parameter points

#endif
