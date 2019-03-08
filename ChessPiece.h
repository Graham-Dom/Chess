#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include "Square.h"

class Square;

class ChessPiece
{

protected:

	const bool color; 
	Square *current_square;
	bool has_moved = false;

public:

	ChessPiece(bool in_color);
	bool get_color();
	const Square* get_square();
	virtual bool is_valid_move(const Square &new_square) = 0;
	void move_to(Square &new_square);
	// Move a piece from one square to another
	void print_move_err_msg();
	void place(Square &starting_square);
	void remove_from_play();
};

class Pawn : public ChessPiece
{
public:
	Pawn(bool in_color);
	virtual bool is_valid_move(const Square &new_square);
};

class Knight : public ChessPiece
{
public: 
	Knight(bool in_color);
	virtual bool is_valid_move(const Square &new_square);
};

class Bishop : public ChessPiece
{
public:
	Bishop(bool in_color);
	virtual bool is_valid_move(const Square &new_square);
};

class Rook : public ChessPiece
{
public:
	Rook(bool in_color);
	virtual bool is_valid_move(const Square &new_square);
};

class Queen : public ChessPiece
{
public:
	Queen(bool in_color);
	virtual bool is_valid_move(const Square &new_square);
};

class King : public ChessPiece
{
public:
	King(bool in_color);
	virtual bool is_valid_move(const Square &new_square);
};

#endif