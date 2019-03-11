#ifndef BOARD_H
#define BOARD_H
#include "Square.h"
#include "ChessPiece.h"
#include <vector>
#include <iostream>

class Board
{
	static const int NUM_SQUARES = 8;
	std::vector<std::vector<Square>> board;

public:

	Board();

	void display();
	
	std::vector<Square> & operator[](int X);
	const std::vector<Square> & operator[](int X) const;

};

#endif