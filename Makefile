CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

initial:
	CXXFLAGS -= -Werror
	CXXFLAGS -= -Wall
	PlayerTests

debug: CXXFLAGS += -g
debug: PieceTests

PieceTests: ChessPiece.cpp Square.cpp PieceTests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

PlayerTests: ChessPiece.cpp Square.cpp Board.cpp Player.cpp PlayerTests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -vfr *.out PieceTests PlayerTests *.dSYM
