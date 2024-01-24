LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: game

main.o: src/main.cpp
	g++ -c "src/main.cpp" -o bin/main.o

game: main.o
	@echo "** Building the game"
	g++ -o bin/game bin/main.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f bin/*
