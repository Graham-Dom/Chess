#include "Player.h"
#include "Board.h"

int main(){

	Board board;
	Player p1(true, board);
	Player p2(false, board);
	board.display();

	return 0;
}