#include "ChessPiece.h"
#include <iostream>
#include <cstdlib>

ChessPiece::ChessPiece(bool in_color):
	current_square(nullptr), color(in_color){}

ChessPiece::~ChessPiece(){}

const Square* ChessPiece::get_square() const
{
	return current_square;
}

void ChessPiece::move_to(Square &new_square)
{
	// Move a piece from one square to another
	if (is_valid_move(new_square)) 
	{
		current_square->remove_piece();
		new_square.set_piece(*this);
		current_square = &new_square;
		has_moved = true;
	}

	else {
		print_move_err_msg();
	}
}

void ChessPiece::print_move_err_msg() const
{
	std::cout << "Invalid move" << std::endl;
}

void ChessPiece::place(Square &starting_square)
{
	assert(starting_square.is_empty());
	current_square = &starting_square;
	current_square->set_piece(*this);
}


void ChessPiece::remove_from_play()
{
	current_square = nullptr;
}

Pawn::Pawn(bool in_color):ChessPiece(in_color){}
Pawn::~Pawn(){};

bool Pawn::is_valid_move(const Square &new_square)
{
	assert(current_square);
	int squares_traveled_vertically = new_square.get_Y() - current_square->get_Y();
	int squares_traveled_horizontally = new_square.get_X() - current_square->get_X();
	
	if (squares_traveled_vertically == 1){
		
		if (squares_traveled_horizontally == 1 || squares_traveled_horizontally == -1){
			return !new_square.is_empty();
		}
		
		else{
			return (new_square.is_empty() && squares_traveled_horizontally == 0);
		}
	}

	else if (squares_traveled_vertically == 2){
		return (!has_moved && squares_traveled_horizontally == 0);
	}

	else return false;
}

Knight::Knight(bool in_color):ChessPiece(in_color){}
Knight::~Knight(){};

bool Knight::is_valid_move(const Square &new_square)
{
	assert(current_square);
	int squares_traveled_vertically = abs(new_square.get_Y() - current_square->get_Y());
	int squares_traveled_horizontally = abs(new_square.get_X() - current_square->get_X());

	return ((squares_traveled_horizontally == 2 && squares_traveled_vertically == 1)
		 || (squares_traveled_horizontally == 1 && squares_traveled_vertically == 2));
}

Bishop::Bishop(bool in_color):ChessPiece(in_color){}
Bishop::~Bishop(){};

bool Bishop::is_valid_move(const Square &new_square){
	assert(current_square);
	int squares_traveled_vertically = abs(new_square.get_Y() - current_square->get_Y());
	int squares_traveled_horizontally = abs(new_square.get_X() - current_square->get_X());

	return (squares_traveled_vertically == squares_traveled_horizontally
		 && squares_traveled_vertically > 0);
}

Rook::Rook(bool in_color):ChessPiece(in_color){}
Rook::~Rook(){};

bool Rook::is_valid_move(const Square &new_square){
	assert(current_square);
	int squares_traveled_vertically = abs(new_square.get_Y() - current_square->get_Y());
	int squares_traveled_horizontally = abs(new_square.get_X() - current_square->get_X());

	return ((squares_traveled_horizontally == 0 && squares_traveled_vertically > 0)
		||  (squares_traveled_vertically == 0 && squares_traveled_horizontally > 0));
}

Queen::Queen(bool in_color):ChessPiece(in_color){}
Queen::~Queen(){};

bool Queen::is_valid_move(const Square &new_square){
	assert(current_square);
	int squares_traveled_vertically = abs(new_square.get_Y() - current_square->get_Y());
	int squares_traveled_horizontally = abs(new_square.get_X() - current_square->get_X());

	return (((squares_traveled_horizontally == 0 && squares_traveled_vertically > 0)
		||  (squares_traveled_vertically == 0 && squares_traveled_horizontally > 0))

		|| (squares_traveled_vertically == squares_traveled_horizontally
		 && squares_traveled_vertically > 0));
}

King::King(bool in_color):ChessPiece(in_color){}
King::~King(){};

bool King::is_valid_move(const Square &new_square){
	assert(current_square);
	int squares_traveled_vertically = abs(new_square.get_Y() - current_square->get_Y());
	int squares_traveled_horizontally = abs(new_square.get_X() - current_square->get_X());

	return ((squares_traveled_vertically == 1 && squares_traveled_horizontally <= 1)
		 || (squares_traveled_horizontally == 1 && squares_traveled_vertically <= 1));
}