all: main.cpp card.h card.cpp card main
main: main.cpp
	g++ -pedantic-errors -g main.cpp card -o main

card: card.h card.cpp
	g++ -pedantic-errors -g -c card.cpp -o card