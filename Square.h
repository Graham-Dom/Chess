#ifndef SQUARE_H
#define SQUARE_H

#include "ChessPiece.h"

class ChessPiece;

class Square
{
	ChessPiece * piece;

public:
	const unsigned short X;
	const unsigned short Y;

	void set_piece(ChessPiece &new_piece);
	// Place a piece on a square
	ChessPiece* get_piece() const;
	void remove_piece();
	bool is_empty() const;
	Square(short X_POS, short Y_POS);
};

#endif