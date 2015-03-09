// sudokugrid.cpp
// Kenneth Toombs, Marcellis Carr-Barfield. 10/17/14

#include "sudokugrid.h"
#include "gridio.h"
using namespace std;

// IMPLEMENT CONSTRUCTOR AND 7 MEMBER FUNCTIONS AS SPECIFIED IN "sudokugrid.h"

SudokuGrid::SudokuGrid(const int problem[9][9]){
    
    //declare local variables
    int i = 0, j = 0;
    
    
    //initiate for loop to iterate through the rows of the array
    for(i=0; i<9; i++){
    	
	//initiate for loop to iterate through the row entries
        for(j=0; j<9; j++){
	  if (problem[i][j] == 0){
	    //if passed an empty value, create an empty space in SudokuSquare array, with
	    //an unfixed boolean value
	    SudokuSquare holder;
	    holder.number = problem[i][j];
	    holder.fixed = 0;
	    array[i][j] = holder;
	  }
	  else{
	    //if passed a non-empty entry, assign the value to the corresponding SudokuSquare entry.
	    //if the entry passed is less than 0 or greater than 9, throw an exception.
	    if (problem[i][j] < 0 || problem[i][j] > 9){
		   throw GridException(DATA);
	    }
	    SudokuSquare holder;
	    holder.number = problem[i][j];
	    holder.fixed = 1;
	    array[i][j] = holder;
	  }
	   
	}

    }

   
   
}


int SudokuGrid::getNumber(int row, int column) const{
  //if the index of the row or columns are invalid, throw an exception
  if (row < 0 || row > 8 || column < 0 || column > 8){
    throw GridException(INDEX);
  }
  //else, go to the structure in the corresponding row and column in the array, and return the 
  //number field
  return array[row][column].number;
}


void SudokuGrid::setNumber(int number, int row, int column){
  //if the row or column indexes are invalid, throw an exception
  if (row < 0 || row > 8 || column < 0 || column > 8){
    throw GridException(INDEX);
  }
  //if the array is fixed at the specified location, throw an exception
  if (array[row][column].fixed == 1){
    throw GridException(RULE);
  }
  //if the number is invalid, throw an exception
  if (number < 0 || number > 9){
    throw GridException(DATA);
  }
  //if all parameters are valid, set the number field in the structure located in the array to
  // the number specified
  array[row][column].number = number;
}


bool SudokuGrid::occursInRow(int number, int row) const{
  //if the row indexes are invalid, throw an exception
  if (row < 0 || row > 8){
    throw GridException(INDEX);
      }
  //for the given row number, iterate throughout the columns(entries) of that row and check
  //if the number specified matches any entries. If so, return true. Else, return false.
  for(int j = 0; j < 9; j++){
    if (array[row][j].number == number){
      return 1;
    }
  }
  return 0;
}


bool SudokuGrid::occursInColumn(int number, int column) const{
  //if the column is invalid, throw and exception
   if (column < 0 || column > 8){
     throw GridException(INDEX);
      }
   //iterate through the rows(column entries) of the specified column and check if the number
   //specified matches any entries. If so, return true. Else, return false.
  for(int i = 0; i < 9; i++){
    if (array[i][column].number == number){
      return 1;
    }
  }
  return 0;
} 



bool SudokuGrid::occursInBox(int number, int row, int column) const{
  /*
    This function separates the grid into 9 large boxes by sorting the column and row indexes.
    once the boxes are separated, it checks the location of the number, finds the corresponding box,
    and checks all values in the box to see if the number given matches any entries. If the entries match
    return true, else return false.
   */




  // if the row or column indexes are invalid, throw an exception
  if (row < 0 || row > 8 || column < 0 || column > 8){
    throw GridException(INDEX);
  }

  if((row == 0 ||row == 1 ||row == 2) && (column == 0 || column == 1 || column == 2)){
    for (int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }

  if((row == 0 ||row == 1 ||row == 2) && (column == 3 || column == 4 || column == 5)){
    for (int i = 0; i < 3; i++){
      for(int j = 3; j < 6; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 0 ||row == 1 ||row == 2) && (column == 6 || column == 7 || column == 8)){
    for (int i = 0; i < 3; i++){
      for(int j = 6; j < 9; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 3 ||row == 4 ||row == 5) && (column == 0 || column == 1 || column == 2)){
    for (int i = 3; i < 6; i++){
      for(int j = 0; j < 3; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 3  ||row == 4 ||row == 5)  && (column == 3 || column == 4 || column == 5)){
    for (int i = 3; i < 6; i++){
      for(int j = 3; j < 6; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 3 ||row == 4 ||row == 5) && (column == 6 || column == 7 || column == 8)){
    for (int i = 3; i < 6; i++){
      for(int j = 6; j < 9; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 6 ||row == 7 ||row == 8) && (column == 0 || column == 1 || column == 2)){
    for (int i = 6; i < 9; i++){
      for(int j = 0; j < 3; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 6 ||row == 7 ||row == 8) && (column == 3 || column == 4 || column == 5)){
    for (int i = 6; i < 9; i++){
      for(int j = 3; j < 6; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  if((row == 6 ||row == 7 ||row == 8) && (column == 6 || column == 7 || column == 8)){
    for (int i = 6; i < 9; i++){
      for(int j = 6; j < 9; j++){
	if (array[i][j].number == number){
	  return 1;
	  }
      }
    }
    return 0;
  }
  return 0;
}


bool SudokuGrid::isCandidate(int number, int row, int column) const{
  //if the row or column indexes are invalid, throw an exception
  if (row < 0 || row > 8 || column < 0 || column > 8){
    throw GridException(INDEX);
  }

  //declare local variables
  bool inBox, inRow, inColumn;

  //use the declared variables to record the values returned by occursInRow, occursInColumn, occursInBox.
  inRow = occursInRow(number, row);
  inColumn = occursInColumn(number, column);
  inBox = occursInBox(number, row, column);
  
  //if the values returned by the above functions are false for the given number, row, and column, then
  //the number specified must be a candidate. Return true if it is a candidate, false otherwise.
  if (inRow == 0 && inColumn == 0 && inBox == 0 && number > -1 && number < 10){
    return 1;
  }
  
  return 0;

}


bool SudokuGrid::isSolved() const{
  /*
    This function checks each row to see if the number one through nine occur in it. If the numbers
    one through nine occur in each and every row, the puzzle must be solved. If there is a single number
    missing from any row, the puzzle is not solved. Return true if solved, false otherwise.
   */
  for(int i = 0; i < 9; i++){
    for(int num = 1; num < 10; num++){
      if (occursInRow(num, i) == 0){
	return 0;
      }
    }
  }
  return 1;
}
