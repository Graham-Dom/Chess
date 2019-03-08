#ifndef SQUARE_H
#define SQUARE_H

#include "ChessPiece.h"

class ChessPiece;

class Square
{
	const unsigned short X;
	const unsigned short Y;
	ChessPiece * piece;

public:
	void set_piece(ChessPiece &new_piece);
	// Place a piece on a square
	ChessPiece* get_piece() const;
	short get_X() const;
	short get_Y() const;
	void remove_piece();
	bool is_empty() const;
	Square(short X_POS, short Y_POS);
};

#endif