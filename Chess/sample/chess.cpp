#include <iostream>
#include <map>
#include <string>

using namespace std;

static int const DIM = 8;

//interface
class ChessInterface{
protected:
  static int chessBoard[DIM][DIM];
  static map<string, int> boardPos;
  virtual void submitMove(string, string) = 0;
  virtual void resetBoard() = 0;
  virtual int move(int, int){return -1;}
  
public:
  void printBoard(){
    for(int i = 0; i < DIM; i++){
      for(int j = 0; j < DIM; j++){
	cout.width(3);
	cout << chessBoard[i][j];
      }
      cout << endl;
    }
  }
};


//ChessBoard class
class ChessBoard : public ChessInterface{
private:
  int getBoardPiece(int pos){
    int xCoord = (pos / 10) - 1;
    int yCoord = (pos % 10) - 1;
    return chessBoard[xCoord][yCoord];
  }
  
protected:
  static int turn; // 0 for white; 1 for black
  static map<int, ChessBoard*> figures;

public:
  bool isMyTurn(int piece){
    if(turn != piece){
      if(piece == 0){
	cout << "It is not White's turn to move!" << endl;
	return 0;
      }
      else{
	cout << "It is not Black's turn to move!" << endl;
	return 0;
      }
    }
    else{
      return 1;
    }
  }

  void flipTurn(){
    turn = (turn + 1) % 2;
  }
  
  //submitMove
  virtual void submitMove(string a, string b){
    if(boardPos.find(a) == boardPos.end()){
      cout << "Position '" << a << "' does not exist!" << endl;
    }
    else if(boardPos.find(b) == boardPos.end()){
      cout << "Position '" << b << "' does not exist!" << endl;
    }
    else if(!getBoardPiece(boardPos[a])){
	cout << "There is no piece at position " << a << "!" << endl;
    }
    else{
      int pieceColor;
      int piece = getBoardPiece(boardPos[a]); 
      int currentPos = boardPos[a];
      int nextPos = boardPos[b];
      (piece > 0) ? pieceColor = 0 : pieceColor = 1;
      
      if(!isMyTurn(pieceColor)){}//a message will be displayed if it is not our turn
      else{  //here we change the board and check if the move is valid
	if(figures[piece]->move(currentPos, nextPos)){  //currently only works for pawns
	  flipTurn();
	}
	cout << a << " to " << b << "!" <<endl; //finish the sentence
      }
    }
    
  }

  //reset board
  virtual void resetBoard(){
    for(int i = 0; i < DIM; i++){
      chessBoard[1][i] = -1;
      chessBoard[6][i] = 1;
      chessBoard[0][i] = (-2 -i) % 7;
      chessBoard[7][DIM - i - 1] = (2 + i) % 7;
    }
    chessBoard[0][5] = -4; chessBoard[0][6] = -3;
    chessBoard[7][1] = 3; chessBoard[7][2] = 4;
    
    for(int i = 2; i < 6; i++){
      for(int j = 0; j < DIM; j++){
	chessBoard[i][j] = 0;
      }
    }

    turn = 0;  //whites are first
    
  }

  //virtual void move(){figures[1]->move();}  //just to try sth

};

int ChessBoard::turn = 0;  //Whites are first to move



//Pawn class
class Pawn : public ChessBoard{
protected:
  int color; //0 for white ; 1 for black
  int successfulMove = 0; //1 if successful
  
public:
  Pawn(int color) : color(color) {}
  
  virtual int move(int p1, int p2) override {
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;

    if(color == 0){  //check when whites move
      if(p1Y == p2Y){  //when moving straight ahead
	if(p2X == p1X - 1 && chessBoard[p2X][p2Y] == 0){
	  successfulMove = 1;
	}
	else if(p2X == p1X - 2 && p1X == 6 && chessBoard[p2X][p2Y] == 0 && chessBoard[p2X - 1][p2Y] == 0){
	  successfulMove = 1;
	}
      }
      else if(p2X == p1X - 1 && abs(p1Y - p2Y) == 1){  //checks if the pawn could take an enemy figure
	if(chessBoard[p2X][p2Y] < 0){
	  successfulMove = 1;
	}
      }
    }
    else{  //check when black moves

      if(p1Y == p2Y){  //when moving straight ahead
	if(p2X == p1X + 1 && chessBoard[p2X][p2Y] == 0){
	  successfulMove = 1;
	}
	else if(p2X == p1X + 2 && p1X == 1 && chessBoard[p2X][p2Y] == 0 && chessBoard[p2X + 1][p2Y] == 0){
	  successfulMove = 1;
	}
      }
      else if(p2X == p1X + 1 && abs(p1Y - p2Y) == 1){  //checks if the pawn could take an enemy figure
	if(chessBoard[p2X][p2Y] > 0){
	  successfulMove = 1;
	}
      }

    }
    //here we put the message for the pawn 
    cout << ((color == 0) ? "White's " : "Black's ");
    if(successfulMove){
      chessBoard[p2X][p2Y] = (color == 0 ? 1 : -1);
      chessBoard[p1X][p1Y] = 0;
      cout << "Pawn moves from ";
      successfulMove = 0;
      return 1;
    }
    else{
      cout << "Pawn cannot move from ";
    }
    
    return successfulMove;  //we should rather check for successful moves only
  }
  
};

int ChessInterface::chessBoard[DIM][DIM] = {{-2,-3,-4,-5,-6,-4,-3,-2},
					    {-1,-1,-1,-1,-1,-1,-1,-1},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {1, 1, 1, 1, 1, 1, 1, 1},
					    {2, 3, 4, 6, 5, 4, 3, 2}
};

map<string, int> ChessInterface::boardPos =
  {
   {"A8", 11}, {"A7", 21}, {"A6", 31}, {"A5", 41}, {"A4", 51}, {"A3", 61}, {"A2", 71}, {"A1", 81},
   {"B8", 12}, {"B7", 22}, {"B6", 32}, {"B5", 42}, {"B4", 52}, {"B3", 62}, {"B2", 72}, {"B1", 82},
   {"C8", 13}, {"C7", 23}, {"C6", 33}, {"C5", 43}, {"C4", 53}, {"C3", 63}, {"C2", 73}, {"C1", 83},
   {"D8", 14}, {"D7", 24}, {"D6", 34}, {"D5", 44}, {"D4", 54}, {"D3", 64}, {"D2", 74}, {"D1", 84},
   {"E8", 15}, {"E7", 25}, {"E6", 35}, {"E5", 45}, {"E4", 55}, {"E3", 65}, {"E2", 75}, {"E1", 85},
   {"F8", 16}, {"F7", 26}, {"F6", 36}, {"F5", 46}, {"F4", 56}, {"F3", 66}, {"F2", 76}, {"F1", 86},
   {"G8", 17}, {"G7", 27}, {"G6", 37}, {"G5", 47}, {"G4", 57}, {"G3", 67}, {"G2", 77}, {"G1", 87},
   {"H8", 18}, {"H7", 28}, {"H6", 38}, {"H5", 48}, {"H4", 58}, {"H3", 68}, {"H2", 78}, {"H1", 88}
  };

map<int, ChessBoard*> ChessBoard::figures =
  {
   {1, new Pawn(0)},  //need a destructor for this
   {-1, new Pawn(1)}
  };

int main(){
  
  ChessBoard cb;
  cb.resetBoard();
  cb.printBoard();
  //cb.move(2, 5);
  //cb.resetBoard();
  //cb.printBoard();
  cb.submitMove("A1", "D17");
  cb.submitMove("A4", "D2");
  cb.submitMove("A7", "D2");
  cb.submitMove("B2", "D2");
  cb.submitMove("C2", "D2");
  cb.submitMove("B7", "D2");
  cb.submitMove("C2", "C4");
  cb.submitMove("C4", "C5");
  cb.submitMove("B7", "B6");
  cb.submitMove("C4", "C5");
  cb.submitMove("B6", "C5");
  cb.submitMove("A2", "A5");
  cb.submitMove("A2", "B3");
  cb.submitMove("A2", "A3");
  cb.submitMove("C5", "C3");

  cb.printBoard();
  return 0;
}
