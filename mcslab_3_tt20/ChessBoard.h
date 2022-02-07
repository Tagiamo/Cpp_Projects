#pragma once

#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::string;
using std::endl;
using std::map;

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
  void printBoard();
};


//ChessBoard class
class ChessBoard : public ChessInterface{
private:
  int getBoardPiece(int pos);
  static int count;
  
protected:
  static int turn; // 0 for white; 1 for black
  static map<int, ChessBoard*> figures;

public:
  ChessBoard();
  
  bool isMyTurn(int piece);
  bool isDestinationFriendly(int color, int p2X, int p2Y);
  bool isCheck(int color, int validate, int p1, int p2);
  bool isCheckMate(int color);
  bool canKingMove(int color);  //used in isCheckMate function
  bool canTakeAttacker(int color);  //used in isCheckMate function
  bool canBlockPath(int color);  //used in isCheckMate function
  void flipTurn();
  void printPiece(int piece);  //prints the name of the piece
  int indexToPos(int coordX, int coordY);

  //submitMove
  virtual void submitMove(string a, string b) override {
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
      int possibleMove = 1;  //checks if our own move won't lead to us being checked
      int validMove = 0;
      int piece = getBoardPiece(boardPos[a]); 
      int currentPos = boardPos[a];
      int nextPos = boardPos[b];
      (piece > 0) ? pieceColor = 0 : pieceColor = 1;
      
      if(!isMyTurn(pieceColor)){}//a message will be displayed if it is not our turn
      else{  //here we change the board if the move is valid

	possibleMove = !isCheck(pieceColor, 1, currentPos, nextPos);  //check our move
	int destinationPiece = getBoardPiece(boardPos[b]);
	if(possibleMove && figures[piece]->move(currentPos, nextPos)){
	  validMove = 1;
	  flipTurn();
	}
	
	cout << a << " to " << b;
	if(possibleMove && validMove && destinationPiece){
	  cout << " taking ";
	  cout << ((destinationPiece > 0) ? "White's ": "Black's ");
	  printPiece(destinationPiece);
	}
	cout << ((validMove) ? "\n" : "!\n");

	//checking if opponent is in check or checkmate
	if(possibleMove && validMove){
	  if(isCheck(pieceColor, 0, -1, -1)){
	    if(isCheckMate(pieceColor)){
	      cout << "mate";
	    }
	    cout << endl;
	  }
	}
	
      }
    }
    
  }

  
  virtual void resetBoard(){
    for(int i = 0; i < DIM; i++){
      chessBoard[1][i] = -1;
      chessBoard[6][i] = 1;
      chessBoard[0][i] = (-2 -i) % 7;
      chessBoard[7][i] = (2 + i) % 7;
    }
    chessBoard[0][5] = -4; chessBoard[0][6] = -3;
    chessBoard[7][5] =  4; chessBoard[7][6] =  3;
    
    for(int i = 2; i < 6; i++){
      for(int j = 0; j < DIM; j++){
	chessBoard[i][j] = 0;
      }
    }

    turn = 0;  //whites are first
    cout << "A new chess game is started!\n";
  }
};

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
	else if(p2X == p1X - 2 && p1X == 6 && chessBoard[p2X][p2Y] == 0 && chessBoard[p2X + 1][p2Y] == 0){
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
	else if(p2X == p1X + 2 && p1X == 1 && chessBoard[p2X][p2Y] == 0 && chessBoard[p2X - 1][p2Y] == 0){
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
    
    return successfulMove;
  }
  
};


//Knight class
class Knight : public ChessBoard{
protected:
  int color; //0 for white; 1 for black
  int successfulMove = 0;

public:
  Knight(int color) : color(color) {}

  virtual int move(int p1, int p2) override {
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;

    if((abs(p1X - p2X) == 2 && abs(p1Y - p2Y) == 1) ||
       (abs(p1X - p2X) == 1 && abs(p1Y - p2Y) == 2))  //checks if the shape is correct
      {
	if((color == 0 && chessBoard[p2X][p2Y] <= 0) ||
	   (color == 1 && chessBoard[p2X][p2Y] >= 0))  //checks for friendly piece
	  {
	    successfulMove = 1;
	  } 
      }
    
    //here we put the message for the knight 
    cout << ((color == 0) ? "White's " : "Black's ");
    if(successfulMove){
      chessBoard[p2X][p2Y] = (color == 0 ? 3 : -3);
      chessBoard[p1X][p1Y] = 0;
      cout << "Knight moves from ";
      successfulMove = 0;
      return 1;
    }
    else{
      cout << "Knight cannot move from ";
    }
    
    return successfulMove;  //reached when move is invalid
  }
};


//Rook class
class Rook : public ChessBoard{
protected:
  int color; //0 for white; 1 for black
  int successfulMove = 1;  //success by default

public:
  Rook(int color) : color(color) {}

  virtual int move(int p1, int p2) override {
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;
    int increment;
    int startOffset;

    if(isDestinationFriendly(color, p2X, p2Y)){
      successfulMove = 0;
    }
    else if(p1X == p2X && p1Y != p2Y){  //horizontal movement
      (p2Y > p1Y) ? increment = 1 : increment = -1;
      (p2Y > p1Y) ? startOffset = 1 : startOffset = -1;
      for(int i = p1Y + startOffset; i != p2Y; i += increment){
	if(chessBoard[p1X][i] != 0){
	    successfulMove = 0;
	    break;
	}
      }
    }
    else if(p1Y == p2Y && p1X != p2X){  //vertical movement
      (p2X > p1X) ? increment = 1 : increment = -1;
      (p2X > p1X) ? startOffset = 1 : startOffset = -1;
      for(int i = p1X + startOffset; i != p2X; i += increment){
	if(chessBoard[i][p1Y] != 0){
	    successfulMove = 0;
	    break;
	}
      }
    }
    else{  //destination not reachable
      successfulMove = 0;
    }
    
    //here we put the message for the knight 
    cout << ((color == 0) ? "White's " : "Black's ");
    if(successfulMove){
      chessBoard[p2X][p2Y] = (color == 0 ? 2 : -2);
      chessBoard[p1X][p1Y] = 0;
      cout << "Rook moves from ";
    }
    else{
      cout << "Rook cannot move from ";
      successfulMove = 1;
      return 0;
    }
    
    return successfulMove;  //reached when move is valid
  }
};

//Bishop class
class Bishop : public ChessBoard{
protected:
  int color; //0 for white; 1 for black
  int successfulMove = 1;  //success by default

public:
  Bishop(int color) : color(color) {}

  virtual int move(int p1, int p2) override {
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;
    int tempX; int tempY;

    //checks if destination is on a diagonal and if destination is friendly
    if(isDestinationFriendly(color, p2X, p2Y) || abs(p2X - p1X) != abs(p2Y - p1Y)){
      successfulMove = 0;
    }
    else if(p2Y > p1Y){  //diagonal move to the right  //make it into a function
      
      if(p2X < p1X){  //move to northeast
	tempX = p1X - 1; tempY = p1Y + 1;
	while(tempX > p2X){
	  if(chessBoard[tempX--][tempY++] != 0){
	    successfulMove = 0;
	    break;
	  }
	}
      }
      else{  //move to southeast
	tempX = p1X + 1; tempY = p1Y + 1;
	while(tempX < p2X){
	  if(chessBoard[tempX++][tempY++] != 0){
	    successfulMove = 0;
	    break;
	  }
	}
      }
      
    }
    else{  //diagonal move to the left
      
      if(p2X < p1X){  //move to northwest
	tempX = p1X - 1; tempY = p1Y - 1;
	while(tempX > p2X){
	  if(chessBoard[tempX--][tempY--] != 0){
	    successfulMove = 0;
	    break;
	  }
	}
      }
      else{  //move to southwest
	tempX = p1X + 1; tempY = p1Y - 1;
	while(tempX < p2X){
	  if(chessBoard[tempX++][tempY--] != 0){
	    successfulMove = 0;
	    break;
	  }
	}
      }
      
    }
    
    //here we put the message for the bishop
    cout << ((color == 0) ? "White's " : "Black's ");
    if(successfulMove){
      chessBoard[p2X][p2Y] = (color == 0 ? 4 : -4);
      chessBoard[p1X][p1Y] = 0;
      cout << "Bishop moves from ";
    }
    else{
      cout << "Bishop cannot move from ";
      successfulMove = 1;
      return 0;
    }
    
    return successfulMove;  //reached when move is valid
  }
};


//King class
class King : public ChessBoard{
protected:
  int color; //0 for white; 1 for black
  int successfulMove = 1;  //success by default

public:
  King(int color) : color(color) {}

  virtual int move(int p1, int p2) override {
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;

    if(isDestinationFriendly(color, p2X, p2Y) || abs(p1X - p2X) != 1 || abs(p1Y - p2Y) != 1){
      successfulMove = 0;
    }
    
    //here we put the message for the king
    cout << ((color == 0) ? "White's " : "Black's ");
    if(successfulMove){
      chessBoard[p2X][p2Y] = (color == 0 ? 6 : -6);
      chessBoard[p1X][p1Y] = 0;
      cout << "King moves from ";
    }
    else{
      cout << "King cannot move from ";
      successfulMove = 1;
      return 0;
    }
    
    return successfulMove;  //reached when move is valid
  }
};


//Queen class
class Queen : public ChessBoard{
protected:
  int color; //0 for white; 1 for black
  int successfulMove = 1;  //success by default

public:
  Queen(int color) : color(color) {}

  virtual int move(int p1, int p2) override {
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;
    int tempX; int tempY;  //if destinatination is on a diagonal

    if(isDestinationFriendly(color, p2X, p2Y)){
      successfulMove = 0;
    }
    else if(abs(p2X - p1X) == abs(p2Y - p1Y)){  //check if position is diagonal

      if(p2Y > p1Y){  //diagonal move to the right
      
	if(p2X < p1X){  //move to northeast
	  tempX = p1X - 1; tempY = p1Y + 1;
	  while(tempX > p2X){
	    if(chessBoard[tempX--][tempY++] != 0){
	      successfulMove = 0;
	      break;
	    }
	  }
	}
	else{  //move to southeast
	  tempX = p1X + 1; tempY = p1Y + 1;
	  while(tempX < p2X){
	    if(chessBoard[tempX++][tempY++] != 0){
	      successfulMove = 0;
	      break;
	    }
	  }
	}
	
      }
      else{  //diagonal move to the left
      
	if(p2X < p1X){  //move to northwest
	  tempX = p1X - 1; tempY = p1Y - 1;
	  while(tempX > p2X){
	    if(chessBoard[tempX--][tempY--] != 0){
	      successfulMove = 0;
	      break;
	    }
	  }
	}
	else{  //move to southwest
	  tempX = p1X + 1; tempY = p1Y - 1;
	  while(tempX < p2X){
	    if(chessBoard[tempX++][tempY--] != 0){
	      successfulMove = 0;
	      break;
	    }
	  }
	}
      
      }
      
    }
    else if(p1X == p2X || p1Y == p2Y){  //check if position is horizontal/vertical
      int increment;
      int startOffset;
      
      if(p1X == p2X){  //horizontal movement
	(p2Y > p1Y) ? increment = 1 : increment = -1;
	(p2Y > p1Y) ? startOffset = 1 : startOffset = -1;
	for(int i = p1Y + startOffset; i != p2Y; i += increment){
	  if(chessBoard[p1X][i] != 0){
	    successfulMove = 0;
	    break;
	  }
	}
      }
      else{  //vertical movement
	(p2X > p1X) ? increment = 1 : increment = -1;
	(p2X > p1X) ? startOffset = 1 : startOffset = -1;
	for(int i = p1X + startOffset; i != p2X; i += increment){
	  if(chessBoard[i][p1Y] != 0){
	    successfulMove = 0;
	    break;
	  }
	}
      }
      
    }
    else{  //then move invalid
      successfulMove = 0;
    }
    
    //here we put the message for the queen
    cout << ((color == 0) ? "White's " : "Black's ");
    if(successfulMove){
      chessBoard[p2X][p2Y] = (color == 0 ? 5 : -5);
      chessBoard[p1X][p1Y] = 0;
      cout << "Queen moves from ";
    }
    else{
      cout << "Queen cannot move from ";
      successfulMove = 1;
      return 0;
    }
    
    return successfulMove;  //reached when move is valid
  }
};

