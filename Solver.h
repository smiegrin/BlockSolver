#ifndef SOLVER_H
#define SOLVER_H

#include "Block.h"
#include "Board.h"
#include <SFML\Graphics\Color.hpp>

class Solver {
	Board* board;
	Block* blocks;
	int currentBlock;
	int numOfBlocks;
	bool exhausted;

public:
	Solver(Board*, Block*, int);
	Block* getCurrentBlock();
	Board* getBoard();
	void step();
	sf::Color colorAt(int,int,int);
};

#endif
