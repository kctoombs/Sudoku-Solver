// sudokusolver.cpp
// Kenneth Toombs, Marcellis Carr-Barfield. 10/18/14

#include <iostream>
using namespace std;

#include "sudokugrid.h"
#include "gridio.h"

// mandatory function to define below main:
void solve(SudokuGrid &);

// helper functions for the solve function
void fillCandidate(SudokuGrid& grid);
void fillRow(SudokuGrid& grid);
void fillRow2(SudokuGrid& grid);
void fillColumn(SudokuGrid& grid);
void fillColumn2(SudokuGrid& grid);

// do not change main
int main() {
    int problem[9][9];

    if ( !getProblem(problem) ) {
        cout << "bad input grid; terminating" << endl;
        return 1;
    }

    try {
        SudokuGrid grid(problem); // object, not pointer this time

        cout << "Problem:" << endl;
        display(&grid);           // so pass address to display
        cout << endl;

        solve(grid);

        if (grid.isSolved())
            cout << "Success! Solution:" << endl;
        else
            cout << "Not successful. Best effort:" << endl;

        display(&grid);
    }

    catch(GridException e) {
        cout << "exception: " << e << endl;
    }

    return 0;
}

// attempt to solve the problem using simple logic rules
void solve(SudokuGrid &grid) {

    // TYPE (MOST OR ALL OF) YOUR SOLUTION HERE
    // DECLARE UTILITY FUNCTIONS (IF ANY) HERE OR ABOVE, BUT DEFINE THEM BELOW
  int loopcount = 0;
  while(grid.isSolved() == 0){
    fillCandidate(grid);
    fillRow(grid);
    fillColumn(grid);
    loopcount++;
    if(loopcount == 30000)
      break;

  }

}


// a function that fills the sudoku grid cells if there is only one possible candidate
// in that cell

void fillCandidate(SudokuGrid& grid) {
  
  //declare loop variables
  int i = 0, j = 0, candNumber = 1, num = 1, candTot = 0;

  for(j = 0; j < 9; j++){
    for(i = 0; i < 9; i++){
      if(grid.getNumber(i, j) == 0){
	for(candNumber = 1; candNumber < 10; candNumber++){
	  if(grid.getNumber(i, j) == 0 && grid.isCandidate(candNumber, i, j) == 1){
	    candTot++;
	    num = candNumber;
	  }	  
     
	 

	}

	if(candTot == 1 && grid.getNumber(i, j) == 0){
	  grid.setNumber(num, i, j);
	}
      }
      candTot = 0;
    }
  }

}
  


void fillRow(SudokuGrid& grid){

  // initialize loop variables
  int i = 0, j = 0, iCopy= 0, jCopy = 0, num = 1, cand = 0;

  //loop through all rows
  for(i = 0; i < 9; i++){
    
    //loop through numbers and examine those not already in row
    for(num = 1; num < 10; num++){
      
      //reset number of candidates
      cand = 0;

      //if the number does not occur in the row
      if(grid.occursInRow(num, i) == 0){
      
	//loop through the row entries
	for(j = 0; j < 9; j++){

	  //if the number is a candidate, increase the total candidate number and copy the location
	  if(grid.getNumber(i, j) == 0 && grid.isCandidate(num, i, j) == 1){
	    	    cand++;
	    iCopy = i;
	    jCopy = j;
	  }


	}
	
	//if only one candidate was counted, set the number at the copied location to the candidate number.
	if(cand == 1 && grid.getNumber(iCopy, jCopy) == 0){
	  grid.setNumber(num, iCopy, jCopy);
	}

      }
    }

  }


}




void fillColumn(SudokuGrid& grid){

  // initialize loop variables
  int i = 0, j = 0, iCopy= 0, jCopy = 0, num = 1, cand = 0;

  //loop through all columns
  for(j = 0; j < 9; j++){
    
    //loop through numbers and examine those not already in column
    for(num = 1; num < 10; num++){

      cand = 0;

      if(grid.occursInColumn(num, i) == 0){
      
	for(j = 0; j < 9; j++){

	  if(grid.getNumber(i, j) == 0 && grid.isCandidate(num, i, j) == 1){
	    cand++;
	    iCopy = i;
	    jCopy = j;
	  }
	
	}
	if(cand == 1 && grid.getNumber(iCopy, jCopy) == 0){
	  grid.setNumber(num, iCopy, jCopy);
	}

      }
    }

  }

}


void fillRow2(SudokuGrid& grid){

  // initialize loop variables
  int i = 0, j = 0, num = 1, a = 0, canCounter = 0, canIndex = 0;
  int canNums[9] = {-99}; //initialize to a value that can never return true

  // iterate through every row
  for(i = 0; i < 9; i++){
    //reset the array when rows change
    for(int k = 0; k < 9; k++){
      canNums[k] = -99;
    }

    //iterate through every possible number
    for(num = 1; num < 10; num++){

      //if the number doesn't occur in row, place the number in the 
      //array at the proper index
      if(grid.occursInRow(num, i) == 0){
	canNums[num-1] = num;
      }

    }

    //check each row for empty cells
    for(j = 0; j < 9; j++){
      //if the cell is empty, check array values to see if they are the only candidate
      if(grid.getNumber(i,j) == 0){

	
	//iterate through array indexes of possible candidates
	for(a = 0; a < 9; a++){
	  //if the value at the stored index is a candidate, record the index
	  //and increment the candidate counter
	  if(canNums[a] != -99){
	    if(grid.isCandidate(canNums[a], i, j) == 1){
	      canCounter++;
	      canIndex = a;    

	    }
	  }
	  //if only one candidate is possible, set the candidate value to the proper
	  //location in the grid.
	  if(canCounter == 1 && grid.isCandidate(canNums[canIndex], i, j) == 1){

	    grid.setNumber(canNums[canIndex], i, j);
	    canNums[canIndex] = -99;
	  }
	  
	}

      }

    }
    

  }


}

void fillColumn2(SudokuGrid& grid){

  // initialize loop variables
  int i = 0, j = 0, num = 1, a = 0, canCounter = 0, canIndex = 0;
  int canNums[9] = {-99}; //initialize to a value that can never return true

  // iterate through every column
  for(j = 0; j < 9; j++){

    //reset the array when columns change
    for(int k = 0; k < 9; k++){
      canNums[k] = -99;
    }

    //iterate through every possible number
    for(num = 1; num < 10; num++){

      //if the number doesn't occur in column, place the number in the 
      //array at the proper index
      if(grid.occursInColumn(num, j) == 0){
	canNums[num-1] = num;
      }

    }

    //check each column for empty cells
    for(i = 0; i < 9; i++){
      //if the cell is empty, check array values to see if they are the only candidate
      if(grid.getNumber(i,j) == 0){

	//iterate through array indexes of possible candidates
	for(a = 0; a < 9; a++){
	  //if the value at the stored index is a candidate, record the index
	  //and increment the candidate counter
	  if(grid.isCandidate(canNums[a], i, j) == 1){
	    canCounter++;
	    canIndex = a;    

	  }
	  //if only one candidate is possible, set the candidate value to the proper
	  //location in the grid.
	  if(canCounter == 1 && grid.isCandidate(canNums[canIndex], i, j) == 1){
	      grid.setNumber(canNums[canIndex], i, j);
	      canNums[canIndex] = -99;
	    
	  }

	}

      }

    }
    

  }


}
