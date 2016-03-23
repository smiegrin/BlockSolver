#include "Solver.h"
#include <SFML\Graphics\Color.hpp>

Solver::Solver(Board* bo, Block* bl, int n) {
	board = bo;
	blocks = bl;
	numOfBlocks = n;
	currentBlock = 0;
	exhausted = false;
}

Block* Solver::getCurrentBlock() { return blocks + currentBlock; }

Board* Solver::getBoard() { return board; }

sf::Color Solver::colorAt(int x, int y, int z) {
	if (board->colAt(x,y,z)) return sf::Color::Color(0,0,0,255);
	else if ((blocks + currentBlock)->colAt(x,y,z)) return sf::Color::Color(255,0,0,255);
	else for (int i = currentBlock - 1; i >= 0; i--) if ((blocks + i)->colAt(x,y,z)) return sf::Color::Color(0,0,255,255);
	return sf::Color::Color(0,0,0,0);
}

void Solver::step() {
	if (exhausted) return;
	if(currentBlock < numOfBlocks - 1) currentBlock++;
	else {
		std::cout << "Solution found\n";
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
							(blocks + i)->colAt(u + x,v + y,w + z))
							conflict = true;
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
	} while (conflict);
}