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

public:

	const bool color;
	ChessPiece(bool in_color);
	virtual ~ChessPiece();
	Square* get_square();
	const Square* get_square() const;
	virtual bool is_valid_move(const Square &new_square) const = 0;
	void move_to(Square &new_square);
	// Move a piece from one square to another
	void place(Square &starting_square);
	void remove_from_play();
	virtual char letter_representation() const = 0;
	bool is_in_play() const;
};

class Pawn : public ChessPiece
{
public:
	Pawn(bool in_color);
	virtual ~Pawn();
	virtual bool is_valid_move(const Square &new_square) const;
	virtual char letter_representation() const;
};

class Knight : public ChessPiece
{
public: 
	Knight(bool in_color);
	virtual ~Knight();
	virtual bool is_valid_move(const Square &new_square) const;
	virtual char letter_representation() const;
};

class Bishop : public ChessPiece
{
public:
	Bishop(bool in_color);
	virtual ~Bishop();
	virtual bool is_valid_move(const Square &new_square) const;
	virtual char letter_representation() const;
};

class Rook : public ChessPiece
{
public:
	Rook(bool in_color);
	virtual ~Rook();
	virtual bool is_valid_move(const Square &new_square) const;
	virtual char letter_representation() const;
};

class Queen : public ChessPiece
{
public:
	Queen(bool in_color);
	virtual ~Queen();
	virtual bool is_valid_move(const Square &new_square) const;
	virtual char letter_representation() const;
};

class King : public ChessPiece
{
public:
	King(bool in_color);
	virtual ~King();
	virtual bool is_valid_move(const Square &new_square) const;
	virtual char letter_representation() const;
};

#endif