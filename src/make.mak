
 
all: classes	
	gcc src/chess.cpp *.o -o chess

classes:
	gcc -c src/chess_*.cpp
	gcc -c src/ui/chess_*.cpp
	gcc -c src/chess_pieces/chess_*.cpp

 