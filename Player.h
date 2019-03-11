#include "ChessPiece.h"
#include "Square.h"
#include "Board.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <memory>

class Player
{
	// Data
	const bool color;
	bool in_check = false;
	std::vector<std::unique_ptr<ChessPiece>> pieces;
	Player *other_player;
	Board &board;

	struct Move
	{
		const Square& start_square;
		const Square& end_square;
		Move(Square& start, Square& end);
	};

	// Methods

	void setup_pieces();
	void set_pawns();
	void set_knights();
	void set_bishops();
	void set_rooks();
	void set_queen();
	void set_king();

	const Square& king_location() const;
	Move get_input_move() const;

	bool is_valid_move(const Move &move) const;
	bool is_valid_destination_square(const Move &move) const;
	bool path_is_clear(const Move &move) const;
	std::vector<const Square*> squares_on_move_path(const Move &move) const;
	bool move_puts_player_in_check(const Move * move);
	
	void move_piece(const Move &move);

	bool checked_other_player(const Move &move);
	void call_check();
	bool in_check_mate();
public:
	Player(bool in_color, Board &board);
	//void take_turn();
};