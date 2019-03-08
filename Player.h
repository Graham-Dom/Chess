#include "ChessPiece.h"
#include "Square.h"
#include <vector>
#include <algorithm>

class Player
{
	// Data
	const bool color;
	bool in_check = false;
	std::vector<ChessPiece> pieces;
	Player *other_player;
	//static Board board;

	struct Move
	{
		const Square& start_square;
		const Square& end_square;
		Move(Square& start, Square& end);
	};

	// Methods

	const Square& king_location() const;
	Move get_input_move() const;

	void give_set_of_pieces(std::vector<ChessPiece> in_pieces);

	bool is_valid_move(const Move &move) const;
	bool is_valid_destination(const Move &move) const;
	bool path_is_clear(const Move &move) const;
	bool move_puts_player_in_check(const Move * move);
	
	void move_piece(const Move &move);

	bool checked_other_player(const Move &move);
	void call_check();
	bool in_check_mate();
public:
	Player(bool in_color);
	void take_turn();
};