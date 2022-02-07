#include "ChessBoard.h"

//ChessInterface member function
void ChessInterface::printBoard(){
    for(int i = 0; i < DIM; i++){
      for(int j = 0; j < DIM; j++){
	cout.width(3);
	cout << chessBoard[i][j];
      }
      cout << endl;
    }
}

//ChessInterface board array -> (+) sign are whites (-) sign are blacks
//(0)-> empty spot   (1)-> pawns   (2)-> rooks   (3)-> knights
//(4)-> bishops      (5)-> queen   (6)-> king
int ChessInterface::chessBoard[DIM][DIM] = {{-2,-3,-4,-5,-6,-4,-3,-2},
					    {-1,-1,-1,-1,-1,-1,-1,-1},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {0, 0, 0, 0, 0, 0, 0, 0},
					    {1, 1, 1, 1, 1, 1, 1, 1},
					    {2, 3, 4, 5, 6, 4, 3, 2}
};

//ChessInterface positions mapping
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

//ChessBoard static variable for whose turn it is
int ChessBoard::turn = 0;  //Whites are first to move

//ChessBoard static variable - helps with printing the starting message
int ChessBoard::count = 0;

//ChessBoard map - from int from chessBoard array to objects (of each piece)
map<int, ChessBoard*> ChessBoard::figures =
  {
   { 1, new Pawn(0)},
   {-1, new Pawn(1)},
   { 2, new Rook(0)},
   {-2, new Rook(1)},
   { 3, new Knight(0)},
   {-3, new Knight(1)},
   { 4, new Bishop(0)},
   {-4, new Bishop(1)},
   { 5, new Queen(0)},
   {-5, new Queen(1)},
   { 6, new King(0)},
   {-6, new King(1)}
  };

//ChessBoard empty constructor
ChessBoard::ChessBoard(){
  count++;
  if(count > 12){  //number of items in 'figures' map
    resetBoard();
  }
}


//ChessBoard private member function
int ChessBoard::getBoardPiece(int pos){
    int xCoord = (pos / 10) - 1;
    int yCoord = (pos % 10) - 1;
    return chessBoard[xCoord][yCoord];
  }

//ChessBoard public member function
bool ChessBoard::isMyTurn(int piece){
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
    else{ //it is our turn
      return 1;
    }
  }

//ChessBoard public member function
bool ChessBoard::isCheck(int color, int validateMove, int p1, int p2){
  int king;
  int kingPos;
  int piece;
  int copyTable[DIM][DIM];
  int copyTurn = turn;
  int isCheck = 0;
  
  for(int i = 0; i < DIM; i++){
    for(int j = 0; j < DIM; j++){   //make a copy of the current board
      copyTable[i][j] = chessBoard[i][j];
    }
  }

  
  if(validateMove){  //check if our move is not fatal for the our king
    (color == 0) ? king = 6 : king = -6;
    int p1X = (p1 / 10) - 1; int p1Y = (p1 % 10) - 1;
    int p2X = (p2 / 10) - 1; int p2Y = (p2 % 10) - 1;
    chessBoard[p2X][p2Y] = chessBoard[p1X][p1Y];  //make the move and see if check occurs
    chessBoard[p1X][p1Y] = 0;
  }  
  else{  //checking if the opponent's king is under attack  //called after a move is made
    (color == 0) ? king = -6 : king = 6;
  }

  //find the position of the desired king
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    if(getBoardPiece(it->second) == king){
      kingPos = it->second;
      break;
    }
  }

  //now check if some piece could take the king
  std::cout.setstate(std::ios_base::failbit);  //blocking messages to cout
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    piece = getBoardPiece(it->second);
    if(piece == 0){continue;}
    else if(figures[piece]->move(it->second, kingPos)){
      isCheck = 1;
      break;
    }
  }
  std::cout.clear();

  if(isCheck){
    cout << ((king > 0) ? "White " : "Black ");
    cout << "is in check";
    if(validateMove){
      cout << "-> Under direct attack - Cannot move from ";
    }
  }
  
  
  for(int i = 0; i < DIM; i++){
      for(int j = 0; j < DIM; j++){    //return the board to its initial state
	chessBoard[i][j] = copyTable[i][j];
      }
    }
  turn = copyTurn;  //return the initial value of turn
  
  return isCheck;
}

//ChessBoard member function
int ChessBoard::indexToPos(int coordX, int coordY){
  int result = (coordX + 1) * 10;
  result += coordY + 1;
  return result;
}

//ChessBoard public member function
void ChessBoard::flipTurn(){
    turn = (turn + 1) % 2;
  }

//ChessBoard public member function
void ChessBoard::printPiece(int piece){
  int absPiece = abs(piece);
  if(absPiece == 1){cout << "Pawn";}
  else if(absPiece == 2){cout << "Rook";}
  else if(absPiece == 3){cout << "Knight";}
  else if(absPiece == 4){cout << "Bishop";}
  else if(absPiece == 5){cout << "Queen";}
  else{cout << "'piece not found'";}
}

//ChessBoard public member function
bool ChessBoard::isDestinationFriendly(int color, int p2X, int p2Y){
  if((color == 0 && chessBoard[p2X][p2Y] > 0) ||
     (color == 1 && chessBoard[p2X][p2Y] < 0)){ 
    return 1;
  }
  
  return 0;  //if empty or enemy at destination
}

//ChessBoard public member function - checks if a king
//can do a legal move after being checked
bool ChessBoard::canKingMove(int color){  //calling with our own color to check for enemy
  int canKingMove = 0;  //no by default
  int king;  //black/white king
  int kingPos;  //integer position of king
  int kingX; int kingY;  //coordinates of the king
  int kingDestination;
  (color == 0) ? king = -6 : king = 6;

  //find the position of the desired king
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    if(getBoardPiece(it->second) == king){
      kingPos = it->second;
      break;
    }
  }

  kingX = (kingPos / 10) - 1;
  kingY = (kingPos % 10) - 1;

  //for loops to find the non friendly adjacent spots
  std::streambuf* old = cout.rdbuf(0);
  int breakCondition = 0;
  for(int i = -1; i < 2; i++){
    if(breakCondition){break;}
    for(int j = -1; j < 2; j++){
      if(i == 0 && j == 0){continue;}
      if((kingX + i) < 0 || (kingX + i) > 7 || (kingY + j) < 0 || (kingY + j) > 7){continue;}
      if(king < 0){  //the enemy piece
	if(chessBoard[kingX + i][kingY + j] < 0){continue;}
	else{
	  kingDestination = ((10 * (kingX + i + 1)) + kingY + j + 1);
	  if(!isCheck(!color, 1, kingPos, kingDestination)){
	    canKingMove = 1;
	    breakCondition = 1;
	    break;
	  }
	}
      }
      if(king > 0){
	if(chessBoard[kingX + i][kingY + j] > 0){continue;}
	else{
	  kingDestination = ((10 * (kingX + i + 1)) + kingY + j + 1);
	  if(!isCheck(!color, 1, kingPos, kingDestination)){
	    canKingMove = 1;
	    breakCondition = 1;
	    break;
	  }
	}
      }

    }
  }
  std::cout.rdbuf(old);
  
  return canKingMove;
}

//Chessboard member function
bool ChessBoard::canTakeAttacker(int color){
  int numAttackers = 0;
  int takeAttacker = 0;
  int king;  //black/white king
  int kingPos;  //integer position of king
  int attackerPos;
  int copyTurn = turn;
  int copyTable[DIM][DIM];
  (color == 0) ? king = -6 : king = 6;  //defines the enemy king

  //find the position of the desired king
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    if(getBoardPiece(it->second) == king){
      kingPos = it->second;
      break;
    }
  }

  for(int i = 0; i < DIM; i++){
    for(int j = 0; j < DIM; j++){   //make a copy of the current board
      copyTable[i][j] = chessBoard[i][j];
    }
  }

  int piece;
  std::streambuf* old = cout.rdbuf(0);
  //find the position of the attacker - we are the attacker ('color')
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    piece = getBoardPiece(it->second);
    if(piece == 0){continue;}
    if(figures[piece]->move(it->second, kingPos)){
      turn = copyTurn;
      for(int i = 0; i < DIM; i++){
	for(int j = 0; j < DIM; j++){    //return the board to its initial state
	  chessBoard[i][j] = copyTable[i][j];
	}
      }
      numAttackers++;
      attackerPos = it->second;
      if(numAttackers > 1){  //we cannot take more than 1 attacking piece
	std::cout.rdbuf(old);
	return 0;
      }
    }
  }
  std::cout.rdbuf(old);

  for(int i = 0; i < DIM; i++){
      for(int j = 0; j < DIM; j++){    //return the board to its initial state
	chessBoard[i][j] = copyTable[i][j];
      }
    }
  turn = copyTurn;  //return the initial value of turn

  
  //here we need to check if we can safely take the attacker
  //if we could take it then takeAttacker = 1
  std::streambuf* oldd = cout.rdbuf(0);
  //check if we can take the attacker without exposing our king
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    piece = getBoardPiece(it->second);
    if(piece == 0){continue;}
    if(figures[piece]->move(it->second, attackerPos)){
      if(!isCheck(color, 0, -1, -1)){  //if attacker can be taken and king not in check
	takeAttacker = 1;
      }
      turn = copyTurn;
      for(int i = 0; i < DIM; i++){
	for(int j = 0; j < DIM; j++){    //return the board to its initial state
	  chessBoard[i][j] = copyTable[i][j];
	}
      }
      if(takeAttacker){
	std::cout.rdbuf(oldd);
	return takeAttacker;  //we can take the attacker safely
      }
    }
  }

  std::cout.rdbuf(oldd);
  
  return takeAttacker;
}

//ChessBoard member function
bool ChessBoard::canBlockPath(int color){
  int canBlock = 0;
  int numAttackers = 0;
  int king;  //black/white king
  int kingX; int kingY;
  int kingPos;  //integer position of king
  int attackerPos;
  int attackerX; int attackerY;
  int copyTurn = turn;
  int copyTable[DIM][DIM];
  (color == 0) ? king = -6 : king = 6;  //defines the enemy king

  //find the position of the desired king
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    if(getBoardPiece(it->second) == king){
      kingPos = it->second;
      break;
    }
  }

  kingX = (kingPos / 10) - 1;
  kingY = (kingPos % 10) - 1;

  for(int i = 0; i < DIM; i++){
    for(int j = 0; j < DIM; j++){   //make a copy of the current board
      copyTable[i][j] = chessBoard[i][j];
    }
  }

  int piece;
  std::streambuf* old = cout.rdbuf(0);
  //find the position of the attacker - we are the attacker ('color')
  for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
    piece = getBoardPiece(it->second);
    if(piece == 0){continue;}
    if(figures[piece]->move(it->second, kingPos)){
      turn = copyTurn;
      for(int i = 0; i < DIM; i++){
	for(int j = 0; j < DIM; j++){    //return the board to its initial state
	  chessBoard[i][j] = copyTable[i][j];
	}
      }
      numAttackers++;
      attackerPos = it->second;
      if(numAttackers > 1){  //we cannot block more than 1 attacking piece
	std::cout.rdbuf(old);
	return 0;
      }
    }
  }
  std::cout.rdbuf(old);

  for(int i = 0; i < DIM; i++){
      for(int j = 0; j < DIM; j++){    //return the board to its initial state
	chessBoard[i][j] = copyTable[i][j];
      }
    }
  turn = copyTurn;  //return the initial value of turn

  attackerX = (attackerPos / 10) - 1;
  attackerY = (attackerPos % 10) - 1;

  if(abs(kingX - attackerX) == 1 && abs(kingY - attackerY) == 1){
    return 0;  //if the attacker is on a spot adjacent to the king
  }
  if(abs(chessBoard[attackerX][attackerY]) == 3){
    return 0;  //if the attacking piece is a knight
  }

  //saving the board spots between the king and the attacker
  int pathSpots[DIM] = {0, 0, 0, 0, 0, 0, 0, 0};  //holding the int positions of each path spot
  if(kingX == attackerX || kingY == attackerY){  //if path a straight line
    if(kingX == attackerX){  //horizontal line
      if(kingY > attackerY){  //if king to the right of attacker
	for(int i = 0; i < abs(kingY - attackerY) - 1; i++){
	  pathSpots[i] = indexToPos(kingX, attackerY + i + 1);
	}
      }
      else{  //if king to the left of attacker
	for(int i = 0; i < abs(kingY - attackerY) - 1; i++){
	  pathSpots[i] = indexToPos(kingX, kingY + i + 1);
	}
      }
    }
    else{  //vertical line
      if(kingX > attackerX){  //the king is below the attacker
	for(int i = 0; i < abs(kingX - attackerX) - 1; i++){
	  pathSpots[i] = indexToPos(attackerX + i + 1, kingY);
	}
      }
      else{  //the king is above the attacker
	for(int i = 0; i < abs(kingX - attackerX) - 1; i++){
	  pathSpots[i] = indexToPos(kingX + i + 1, kingY);
	}
      }
    }
  }
  else{  //if attacker on a diagonal
    if((attackerX < kingX) && (attackerY > kingY)){  //attacker is northeast relative to the king
      for(int i = 0; i < abs(kingX - attackerX) - 1; i++){
	pathSpots[i] = indexToPos(kingX - i - 1, kingY + i + 1);
      }
    }
    else if((attackerX < kingX) && (attackerY < kingY)){  //attacker is northwest relative to the king
      for(int i = 0; i < abs(kingX - attackerX) - 1; i++){
	pathSpots[i] = indexToPos(kingX - i - 1, kingY - i - 1);
      }
    }
    else if((attackerX > kingX) && (attackerY < kingY)){  //attacker is southwest relative to the king
      for(int i = 0; i < abs(kingX - attackerX) - 1; i++){
	pathSpots[i] = indexToPos(kingX + i + 1, kingY - i - 1);
      }
    }
    else{  //attacker is southeast relative to the king
      for(int i = 0; i < abs(kingX - attackerX) - 1; i++){
	pathSpots[i] = indexToPos(kingX + i + 1, kingY + i + 1);
      }
    }
  }


  //it is left to check if we can put any friendly pieces on the array spots
  //and not be in check
  std::streambuf* oldd = cout.rdbuf(0);
  for(int i = 0; i < DIM; i++){
    if(pathSpots[i] == 0 || canBlock){break;}
    else{
      //loop through the board - can a blocking move prevent a check
      for(map<string, int>::iterator it = boardPos.begin(); it != boardPos.end(); ++it){
	piece = getBoardPiece(it->second);
	//check if the figure is of right color
	if(color == 0 && piece >= 0){continue;}
	if(color != 0 && piece <= 0){continue;}
	if(figures[piece]->move(it->second, pathSpots[i])){
	  if(!isCheck(color, 0, -1, -1)){  //if king no longer in check
	    canBlock = 1;
	  }
	  turn = copyTurn;
	  for(int i = 0; i < DIM; i++){
	    for(int j = 0; j < DIM; j++){    //return the board to its initial state
	      chessBoard[i][j] = copyTable[i][j];
	    }
	  }
	  if(canBlock){break;}
	}
      }
      //end of for loop
    }
  }
  std::cout.rdbuf(oldd);
  
  return canBlock;
}

//ChessBoard member function
bool ChessBoard::isCheckMate(int color){
  int isCheckMate = 1;
  
  if(canKingMove(color)){  //checks if the king can escape on his own
    isCheckMate = 0;
    return isCheckMate;
  }
  if(canTakeAttacker(color)){  //checks if we can safely take the attacker
    isCheckMate = 0;
    return isCheckMate;
  }
  if(canBlockPath(color)){  //checks if we can block attacker's path
    isCheckMate = 0;
    return isCheckMate;
  }

  return isCheckMate;
}
