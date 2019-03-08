#include "Square.h"

void Square::set_piece(ChessPiece &new_piece)
{
	if (!this->is_empty()){
		piece->remove_from_play();
	}
	piece = &new_piece;
}

ChessPiece* Square::get_piece() const
{
	return piece;
}

short Square::get_X() const
{
	return X;
}

short Square::get_Y() const
{
	return Y;
}

void Square::remove_piece()
{
	piece = nullptr;
}

bool Square::is_empty() const
{
	return (piece == nullptr);
}


Square::Square(short X_POS, short Y_POS): X(X_POS), Y(Y_POS), piece(nullptr){};