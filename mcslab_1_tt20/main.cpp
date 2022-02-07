#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

  char board[9][9];
  
  /* This section illustrates the use of the pre-supplied helper functions. */
  
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  
  
  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";
  
  cout << "=================== Question 2 ===================" << "\n\n";

  // should be OK
  load_board("easy.dat", board);
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // test with a string longer than 2 characters - NOT OK
  load_board("easy.dat", board);
  cout << "Putting '1' into I87 is ";
  if (!make_move("I87", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // number out of bounds test - NOT OK
  load_board("easy.dat", board);
  cout << "Putting '0' into B5 is ";
  if (!make_move("B1", '0', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // position out of bounds test - NOT OK
  load_board("easy.dat", board);
  cout << "Putting '1' into K8 is ";
  if (!make_move("K8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  
  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  cout << '\n';
  
  cout << "=================== Question 4 ===================" << "\n\n";
  
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  
  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  // write more tests
  
  cout << "=================== Question 5 ===================" << "\n\n";

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found for 'mystery2'." << '\n';
    //display_board(board);
  }
  cout << '\n';
  
  // in order to time the solutions for mystery1 and mystery3
  auto start_mystery1 = high_resolution_clock::now();
  
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
    //display_board(board);
  }
  cout << '\n';

  auto stop_mystery1 = high_resolution_clock::now();
  
  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
    //display_board(board);
  }
  cout << '\n';

  auto stop_mystery3 = high_resolution_clock::now();

  auto mystery1_time = duration_cast<microseconds>(stop_mystery1 - start_mystery1);
  auto mystery3_time = duration_cast<microseconds>(stop_mystery3 - stop_mystery1);

  cout << " Time for mystery1.dat solution in microseconds: " << mystery1_time.count() << endl;
  cout << " Time for mystery3.dat solution in microseconds: " << mystery3_time.count() << endl;
  
  return 0;
}
