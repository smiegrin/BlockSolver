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
	int numOfSolutions;
	bool exhausted;

public:
	Solver(Board*, Block*, int);
	Block* getCurrentBlock();
	Board* getBoard();
	bool colAt(int,int,int);
	void step();
	sf::Color colorAt(int,int,int);
};

#endif
