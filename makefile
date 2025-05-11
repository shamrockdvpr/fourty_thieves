all: main
main: main.cpp card.cpp gamespace.cpp
	g++ -pedantic-errors -lstdc++ -g main.cpp card.cpp gamespace.cpp -o main