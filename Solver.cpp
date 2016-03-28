#include "Solver.h"
#include <SFML\Graphics\Color.hpp>

Solver::Solver(Board* bo, Block* bl, int n) {
	board = bo;
	blocks = bl;
	numOfBlocks = n;
	usedBlocks = new bool[n];
	for(int i = 0; i < n; i++) *(usedBlocks + i) = false;
	currentSpace = 0;
	exhausted = false;
}

int Solver::getCurrentSpace() { return currentSpace; }

Board* Solver::getBoard() { return board; }

sf::Color Solver::colorAt(int x, int y, int z) {

	return sf::Color::Color(0,0,0,0);
}

void Solver::step() {
	if (exhausted) return;
	int u,v,w = 0;

	//advance to empty space
	bool found = true;
	do {
		u = currentSpace % board->getWidth();
		v = currentSpace/board->getWidth() % board->getHeight();
		w = currentSpace/(board->getWidth() * board->getHeight());
		for (int i = 0; i < numOfBlocks; i++) {
			if (*(usedBlocks + i) && (blocks + i)->colAt(u,v,w)) found = false;
		}
		if (board->colAt(u,v,w)) found = false;
		if (!found) currentSpace++;
		if (currentSpace > board->getWidth() *
			board->getHeight() *
			board->getDepth()) {
				std::cout << "Solution Found\n";
				//back out of solution
		}
	} while (!found);

	//cycle through unused blocks to fill space

	/*old "Block First" algorythm
	if(currentBlock < numOfBlocks - 1) currentBlock++;
	else {
		std::cout << "Solution found\n";
		(blocks + currentBlock)->setCoordinates(
			(blocks + currentBlock)->getX() + 1,
			(blocks + currentBlock)->getY(),
			(blocks + currentBlock)->getZ());
	}
	bool conflict = false;
	do {
		conflict = false;

		int x = (blocks + currentBlock)->getX();
		int y = (blocks + currentBlock)->getY();
		int z = (blocks + currentBlock)->getZ();
		for(int w = 0; w < (blocks + currentBlock)->getDepth(); w++) {
			if (conflict) break;
			for(int v = 0; v < (blocks + currentBlock)->getHeight(); v++) {
				if (conflict) break;
				for(int u = 0; u < (blocks + currentBlock)->getWidth(); u++) {
					if (conflict) break;
					for (int i = currentBlock-1; i >= 0; i--) {
						if (conflict) break;
						if ((blocks + currentBlock)->colAt(u + x,v + y,w + z) &&
							((blocks + i)->colAt(u + x,v + y,w + z) || board->colAt(u+x,v+y,w+z)))
							conflict = true;
						if (currentBlock == 0 && blocks->colAt(u+x,v+y,w+z) && board->colAt(u+x,v+y,w+z)) conflict = true;
					}
				}
			}
		}

		if (conflict) {	
			(blocks + currentBlock)->setCoordinates(
				(blocks + currentBlock)->getX()+1,
				(blocks + currentBlock)->getY(),
				(blocks + currentBlock)->getZ());
			if((blocks + currentBlock)->getX() + (blocks + currentBlock)->getWidth() > board->getWidth()) {
				(blocks + currentBlock)->setCoordinates(
					0,
					(blocks + currentBlock)->getY()+1,
					(blocks + currentBlock)->getZ());
			}
			if((blocks + currentBlock)->getY() + (blocks + currentBlock)->getHeight() > board->getHeight()) {
				(blocks + currentBlock)->setCoordinates(
					0,
					0,
					(blocks + currentBlock)->getZ()+1);
			}	
			if((blocks + currentBlock)->getZ() + (blocks + currentBlock)->getDepth() > board->getDepth()) {
				if(!(blocks + currentBlock)->rotate()) {
					currentBlock--;
					if(currentBlock < 0) {
						exhausted = true;
						currentBlock = numOfBlocks - 1;
						return;
					}
					(blocks + currentBlock)->setCoordinates(
						(blocks + currentBlock)->getX() + 1,
						(blocks + currentBlock)->getY(),
						(blocks + currentBlock)->getZ());
				}
				else (blocks + currentBlock)->setCoordinates(0,0,0);
			}
		}
	} while (conflict);*/
}