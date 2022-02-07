#ifndef SUDOKU_H
#define SUDOKU_H

/* a function that reads in characters from the file with name
 filename into the 2D character array board */
void load_board(const char* filename, char board[9][9]);

/* a function which displays the 2D character array board in a nice form */
void display_board(const char board[9][9]);

/* a function which returns true if all the positions on the 
   9x9 sudoku board are numbers and false otherwise */
bool is_complete(const char board[9][9]);

/* A function which checks if the digit to be placed is valid and 
   if so it adds is to the 2D array 'board'. The function returns
   true/false if the position, digit is valid/invalid */
bool make_move(const char position[], char digit, char board[9][9]);

/* A function that outputs the 2D array board to 'filename' */
bool save_board(const char* filename, char board[9][9]);

/* A function that returns true if the sudoku is solvable and 
   consequently returns the solution via the 9x9 char array board */
bool solve_board(char board[9][9]);

#endif
