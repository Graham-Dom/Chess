#include "ChessPiece.h"
#include "Square.h"
#include "Board.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <regex>

class Player
{
	const bool color;
	bool in_check = false;
	std::vector<std::unique_ptr<ChessPiece>> pieces;
	Player *other_player;
	Board &board;

	struct Move
	{
		Square& start_square;
		Square& end_square;
		Move(Square& start, Square& end);
	};

	void setup_pieces();
	void set_pawns();
	void set_knights();
	void set_bishops();
	void set_rooks();
	void set_queen();
	void set_king();

	Square& king_location() const;

	Move get_input_move() const;

	bool is_valid_move(const Move &move) const;
	bool is_valid_destination_square(const Move &move) const;
	bool path_is_clear(const Move &move) const;
	std::vector<Square*> squares_on_move_path(const Move &move) const;
	bool move_puts_player_in_check(const Move &move);
	
	void move_piece(const Move &move);

	bool checked_other_player(const Move &move) const;
	void call_check();
	bool in_check_mate();
	bool can_block_capture_path();
	std::vector<Square*> king_capture_path();
	bool king_can_escape();
public:
	Player(bool in_color, Board &board);
	void introduce_other_player(Player *other);
	Player * get_other_player();
	bool take_turn();
};