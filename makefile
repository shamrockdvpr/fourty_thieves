all: main.cpp card.h card.cpp gamespace.cpp card gamespace main
main: main.cpp gamespace.h move.h
	g++ -pedantic-errors -g main.cpp card gamespace -o main

card: card.h card.cpp
	g++ -pedantic-errors -g -c card.cpp -o card

gamespace: gamespace.h gamespace.cpp
	g++ -pedantic-errors -g -c gamespace.cpp -o gamespace