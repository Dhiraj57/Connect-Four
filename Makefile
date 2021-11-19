all: compile link 

compile:
	g++ -I src/include -c main.cpp -c src/DrawBoard.cpp -c src/DrawTile.cpp -c src/DrawText.cpp -c src/Win.cpp 
link:
	g++ main.o DrawBoard.o DrawTile.o DrawText.o Win.o -o Connect -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio 