all: main card move list
main: main.cpp
	g++ -pedantic-errors -g main.cpp card move -o main

card: card.h card.cpp
	g++ -pedantic-errors -g -c card.cpp move -o card

move: move.h
	g++ -pedantic-errors -g -c move.h -o move

list: linkedList.h stack.h doubleLinkedList.h binaryTree.h binarySearchTree.h node.h
	g++ -pedantic-errors -g -c linkedList.h -o list