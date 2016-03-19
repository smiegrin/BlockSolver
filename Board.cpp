#include "Board.h"

Board::Board(int w, int h, int d, bool* s) {
	width = w;
	height = h;
	depth = d;
	space = s;
}

bool Board::colAt(int x, int y, int z) {
	if (x < 0 || x > width ||
		y < 0 || y > height ||
		z < 0 || z > depth) return false;
	return (*(space + x + width*y + width*height*z));
}

int Board::getWidth() { return width; }

int Board::getHeight() { return height; }

int Board::getDepth() { return depth; }