#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* A function which takes a 9x9 array of characters (Sudoku board)
   and decides if all positions are occupied by numbers between 1 and 9  */
bool is_complete(const char board[9][9]){
  
  for (int row = 0; row < 9; row++){
    for (int col = 0; col < 9; col++){
      if (board[row][col] < '1' || board[row][col] > '9')
	return false;
    }
  }
  
  return true;
}

/* A function which checks if the 2-character position string is valid.
   Checks if the string consists of 2 characters and if they are in bounds.
   Returns true if valid. This function is used in function make_move */
bool is_position_possible(const char position[]){

  if (position[2] != '\0')
    return false;
  
  if (position[0] < 'A' || position[0] > 'I')
    return false;

  if (position[1] < '1' || position[1] > '9')
    return false;

  return true;
}

/* A function which checks if the digit to be placed is an integer
   between 1 and 9. Returns true if the digit is valid. Function
   used in make_move */
bool is_digit_possible(char digit){
  
  if (digit < '1' || digit > '9')
    return false;

  return true;
}

/* A function which decides whether the digit to be placed already
   exists in the 3x3 subsquare around it. 
   row -> the row of the digit; col -> the column of the digit */
bool is_subsquare_valid(int row, int col, char digit, char board[9][9]){
  int subsquare_row = row / 3;
  int subsquare_col = col / 3;

  int subsquare_row_center = 1;
  int subsquare_col_center = 1;

  // will set the coordinates of the subsquare center value
  for (int i = 0; i < 3; i++){
    if (subsquare_row == i)
      subsquare_row_center += i * 3;

    if (subsquare_col == i)
      subsquare_col_center += i * 3;
  }

  // checks if the 3x3 subsquare already contains the digit to be placed
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++){
      if (board[subsquare_row_center + i][subsquare_col_center + j] == digit)
	return false;
    }
  }
  
  return true;
}

/*A function which decides if a move is valid and if so it 
  places the digit onto the 2D array 'board'.*/
bool make_move(const char position[], char digit, char board[9][9]){

  // verifies 'position' and 'digit'
  if ( !(is_position_possible(position)) || !(is_digit_possible(digit)) )
    return false;

  int row = (int) (position[0] - 'A');
  int col = (int) (position[1] - '1');

  // checks if the 'digit' is present in the current row or column
  for (int i = 0; i < 9; i++){
    if (board[row][i] == digit || board[i][col] == digit)
      return false;
  }

  // checks for the same number in the closest enclosing square
  if (!(is_subsquare_valid(row, col, digit, board)))
    return false;

  // placing the 'digit' in the 9x9 array 'board'
  board[row][col] = digit;
  return true;
}

/* A function that outputs the 2D array board to 'filename' */
bool save_board(const char* filename, char board[9][9]){
  
  ofstream out(filename);
  if (!out){
    return false;
  }

  int row = 0;
  while (out && row < 9){
    for (int col = 0; col < 9; col++){
      char entry = board[row][col];
      if (entry == '.' || (entry >= '1' && entry <= '9')){
	out << entry;
      }
      else{
	out.close();
	return false;
      }
    }
    row++;
    out << "\n";
  }
  
  out.close();
  return true;
}

/* A function which duplicates the values from 'board' to 'temp_board', 
   each is a 9x9 character array */
void board_duplicate(char board[9][9], char temp_board[9][9]){
  for (int row = 0; row < 9; row++){
    for (int col = 0; col < 9; col++){
      temp_board[row][col] = board[row][col];
    }
  }
}

/* A function to solve the sudoku from the 9x9 board array. The function
   returns true if a solution is found and the corresponding solution 
   is stored in the board array. Returns false if no solution is found */
bool solve_board(char board[9][9]){

  // enter if solution found -> base case
  if (is_complete(board)){
    //save_board("some_sol.dat", board);
    return true;
  }

  // creating a board copy for each stack frame
  char temp_board[9][9];
  board_duplicate(board, temp_board);

  int row_start = static_cast<int>('A');
  int col_start = static_cast<int>('1');
  int first_digit = static_cast<int>('1');

  char row, col, digit;
  bool solution_found;
  bool one_step_back = false;

  /* going through each empty spot from top left to bottom right.
     If a number cannot be placed we return to the previous step. */
  for (int r = 0; r < 9; r++){
    row = static_cast<char>(row_start + r);
    
    for (int c = 0; c < 9; c++){
      
      if (board[r][c] == '.'){
	col = static_cast<char>(col_start + c);
	const char position[3] = {row, col};

	for (int num = 0; num < 9; num++){
	  digit = static_cast<char>(first_digit + num);

	  if (make_move(position, digit, temp_board)){

	    // 'solution_found' is 'true' only if a final solution is found
	    // Here we push another stack frame on top of the current one
	    // and try to guess the next number in the sudoku.
	    solution_found = solve_board(temp_board);
	    if (solution_found){
	      // we make sure that the final sudoku board solution from
	      // 'temp_board' is passed to the sudoku 'board' from the previous
	      // stack - until all the stack frames are popped
	      board_duplicate(temp_board, board);
	      return true;
	    }
	    
	  }
	
	
	}
	// pop the current stack frame if no number
	// could be placed on the current empty spot.
	return one_step_back;
	
      }
      
    }
    
  }
  
  // this should not be reached
  return false;  
}
