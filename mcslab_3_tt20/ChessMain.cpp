#include"ChessBoard.h"
#include<iostream>

//using std::cout;  //should get rid of the using namespace std in the header file

int main() {
  
  
	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cout << '\n';

	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';

	cb.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	//cb.printBoard();
	//cb.submitMove("F2","F3");
	//cb.submitMove("D1","D2");
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	//cb.printBoard();
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';
	//cb.printBoard();
	//cb.submitMove("A8", "B8");
	//cb.submitMove("A7", "A6");
	//cb.submitMove("B6", "B5");
	//cb.submitMove("C7", "C6");
	//cb.submitMove("D7", "C5");
	//cb.submitMove("F6", "F7");
	//cb.submitMove("H8", "F7");

	//ChessBoard ss;
	cb.resetBoard();
	//cb.printBoard();
	cb.submitMove("E2","E4");
	
	cb.submitMove("E7","E5");
	cb.submitMove("F2","F4");
	cb.submitMove("F8","B4");
	cb.submitMove("D2","D3");
	//cb.submitMove("B4","D2");
	//cb.submitMove("E1","D2");
	cb.printBoard();
	
	return 0;
}
