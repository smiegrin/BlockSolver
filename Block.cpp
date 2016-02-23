#include "Block.h"

Block::Block() {};

Block::Block(int newWidth, int newHeight, int newDepth) {
	width = newWidth;
	height = newHeight;
	depth = newDepth;

	//space = new int[width][height][depth];
}

int Block::getWidth() { return width; }
int Block::getHeight() { return height; }
int Block::getDepth() { return depth; }
int Block::getX() {return x; }
int Block::getY() { return y; }
int Block::getZ() { return x; }
int Block::getRotation() { return rotation; }
int Block::getMaxRotation() { return maxRotation; }

int Block::rotate() {
	rotation++;
	if (rotation == maxRotation) rotation = 0;
	return rotation;
}
	