#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include "Square.h"

class Square;

class ChessPiece
{

protected:

	Square *current_square;
	bool has_moved = false;
	void print_move_err_msg() const;

public:

	const bool color;
	ChessPiece(bool in_color);
	virtual ~ChessPiece();
	const Square* get_square() const;
	virtual bool is_valid_move(const Square &new_square) = 0;
	void move_to(Square &new_square);
	// Move a piece from one square to another
	void place(Square &starting_square);
	void remove_from_play();
};

class Pawn : public ChessPiece
{
public:
	Pawn(bool in_color);
	virtual ~Pawn();
	virtual bool is_valid_move(const Square &new_square);
};

class Knight : public ChessPiece
{
public: 
	Knight(bool in_color);
	virtual ~Knight();
	virtual bool is_valid_move(const Square &new_square);
};

class Bishop : public ChessPiece
{
public:
	Bishop(bool in_color);
	virtual ~Bishop();
	virtual bool is_valid_move(const Square &new_square);
};

class Rook : public ChessPiece
{
public:
	Rook(bool in_color);
	virtual ~Rook();
	virtual bool is_valid_move(const Square &new_square);
};

class Queen : public ChessPiece
{
public:
	Queen(bool in_color);
	virtual ~Queen();
	virtual bool is_valid_move(const Square &new_square);
};

class King : public ChessPiece
{
public:
	King(bool in_color);
	virtual ~King();
	virtual bool is_valid_move(const Square &new_square);
};

#endif