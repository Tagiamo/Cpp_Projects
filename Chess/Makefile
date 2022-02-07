chess: ChessMain.o ChessBoard.o
	g++ -g ChessMain.o ChessBoard.o -o chess
ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp
ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp
clean:
	rm -f *.o chess
