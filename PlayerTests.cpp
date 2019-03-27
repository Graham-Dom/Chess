#include "Player.h"
#include "Board.h"

int main(){

	Board board;
	Player p1(true, board);
	Player p2(false, board);
	p1.introduce_other_player(&p2);
	p2.introduce_other_player(&p1);
	board.display();
	p1.take_turn();
	board.display();
	p2.take_turn();
	board.display();
	p1.take_turn();
	board.display();
	p2.take_turn();
	board.display();
	return 0;
}