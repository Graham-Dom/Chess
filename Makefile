CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic

debug: CXXFLAGS += -g
debug: PieceTests

PieceTests: ChessPiece.cpp Square.cpp PieceTests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -vfr *.out PieceTests *.dSYM
