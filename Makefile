CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic

initial:
	CXXFLAGS -= -Werror
	CXXFLAGS -= -Wall
	PlayerTests

debug: CXXFLAGS += -g
debug: PlayerTests

Game: ChessPiece.cpp Square.cpp Board.cpp Player.cpp game.cpp
	 $(CXX) $(CXXFLAGS) $^ -o $@

PieceTests: ChessPiece.cpp Square.cpp PieceTests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

PlayerTests: ChessPiece.cpp Square.cpp Board.cpp Player.cpp PlayerTests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -vfr *.out PieceTests PlayerTests Game *.dSYM
