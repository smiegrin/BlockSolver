#include "Solver.h"
#include <SFML\Graphics\Color.hpp>
#include <iostream>

Solver::Solver(Board* bo, Block* bl, int n) {
	board = bo;
	blocks = bl;
	numOfBlocks = n;
	currentBlock = 0;
	numOfSolutions = 0;
	exhausted = false;
}

Block* Solver::getCurrentBlock() { return blocks + currentBlock; }

Board* Solver::getBoard() { return board; }

bool Solver::colAt(int x, int y, int z) {
	if (board->colAt(x,y,z)) return true;
	for (int i = currentBlock; i >= 0; i--) {
		if ((blocks + i)->colAt(x,y,z)) return true;
	}
	return false;
}

sf::Color Solver::colorAt(int x, int y, int z) {
	if (board->colAt(x,y,z)) return sf::Color::Color(0,0,0,255);
	else if ((blocks + currentBlock)->colAt(x,y,z)) return sf::Color::Color(255,0,0,255);
	else for (int i = currentBlock - 1; i >= 0; i--) if ((blocks + i)->colAt(x,y,z)) return sf::Color::Color(0,255-(50*i),(50*i + 50)%255,255);
	return sf::Color::Color(0,0,0,0);
}

char Solver::getCharAt(int x, int y ,int z) {
	if (board->colAt(x,y,z)) return '#';
	for (int i = 0; i < numOfBlocks; i++) if ((blocks + i)->colAt(x,y,z)) return ('a'+i);
	return ' ';
}

bool Solver::step() {
	//std::cout <<currentBlock<<std::endl;
	if (exhausted) return false;
	if(currentBlock < numOfBlocks - 1) currentBlock++;
	else {
		numOfSolutions++;
		std::cout << "Solution " << numOfSolutions << " found\n";
		(blocks + currentBlock)->setCoordinates(
			(blocks + currentBlock)->getX() + 1,
			(blocks + currentBlock)->getY(),
			(blocks + currentBlock)->getZ());
	}
	bool conflict = false;
	do {
		conflict = false;

		//position block
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
					}
					if (currentBlock == 0 && blocks->colAt(u+x,v+y,w+z) && board->colAt(u+x,v+y,w+z)) conflict = true;
				}
			}
		}

		//check for imposible space
		//choose space
		for (int w = 0; w < board->getDepth(); w++) {
			if (conflict) break;
			for (int v = 0; v < board->getHeight(); v++) {
				if (conflict) break;
				for (int u = 0; u < board->getWidth(); u++) {
					if (conflict) break;
					//check if it's already filled
					if (!colAt(u,v,w)) {
						//check if it's fillable using remaining blocks
						bool found = false;
						for(int j = currentBlock + 1; j < numOfBlocks; j++) { //chose block
							do {
								int x = (blocks + j)->getWidth();
								int y = (blocks + j)->getHeight();
								int z = (blocks + j)->getDepth();
								//position block
								for (int n = z-1; n >= 0; n--) {
									if(found) break;
									for (int m = y-1; m >= 0; m--) {
										if(found) break;
										for (int l = x-1; l >= 0; l--) {
											(blocks + j)->setCoordinates(u-l,v-m,w-n);
											found = true;
											for (int c = z-1; c >=0; c--) {
												for (int b = y-1; b >= 0; b--) {
													for (int a = x-1; a >= 0; a--) {
														if((blocks + j)->colAt(u+a-l,v+b-m,w+c-n) && colAt(u+a-l,v+b-m,w+c-n)) found = false;
													}
												}
											}
											if (found) break;
										}		
									}
								}
								if (found) break;
							} while ((blocks + j)->rotate()); //check using all rotations
							(blocks + j)->setCoordinates(0,0,0);
							if (found) break;							
						}
						if (!found) conflict = true;
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
					(blocks + currentBlock)->setCoordinates(0,0,0);
					currentBlock--;
					if(currentBlock < 0) {
						exhausted = true;
						currentBlock = numOfBlocks - 1;
						return false;
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

	if (currentBlock == numOfBlocks -1) return true;
	else return false;
}
