#ifndef SOLVER_H
#define SOLVER_H

#include "Block.h"
#include "Board.h"
#include <SFML\Graphics\Color.hpp>

class Solver {
	Board* board;
	Block* blocks;
	int currentSpace;
	int numOfBlocks;
	bool exhausted;
	bool* usedBlocks;

public:
	Solver(Board*, Block*, int);
	int getCurrentSpace();
	Board* getBoard();
	void step();
	sf::Color colorAt(int,int,int);
};

#endif
