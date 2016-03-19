#include "Solver.h"
#include <SFML\Graphics\Color.hpp>

Solver::Solver(Board* bo, Block* bl, int n) {
	board = bo;
	blocks = bl;
	numOfBlocks = n;
	currentBlock = 0;
}

Block* Solver::getCurrentBlock() { return blocks + currentBlock; }

sf::Color Solver::colorAt(int x, int y, int z) {
	if (board->colAt(x,y,z)) return sf::Color::Color(0,0,0,255);
	else return sf::Color::Color(0,0,0,0);
}

void Solver::step() {

}