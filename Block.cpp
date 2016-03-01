#include "Block.h"

Block::Block() {};

Block::Block(int newWidth, int newHeight, int newDepth, int mRot,int *rots, bool*newSpace) {
	width = newWidth;
	height = newHeight;
	depth = newDepth;

	maxRotation = mRot;
	rotations = rots;

	space = newSpace;
}

int Block::getWidth() { return width; }
int Block::getHeight() { return height; }
int Block::getDepth() { return depth; }
int Block::getX() {return x; }
int Block::getY() { return y; }
int Block::getZ() { return z; }
int Block::getRotation() { return currentRotation; }
int Block::getMaxRotation() { return maxRotation; }

int Block::rotate() {
	currentRotation++;
	if (currentRotation == maxRotation) currentRotation = 0;
	return currentRotation;
}

void Block::printInfo() {
	std::cout <<
		"Width: " << width << std::endl <<
		"Height: " << height << std::endl <<
		"Depth: " << depth << std::endl <<
		"MaxRotation: " << maxRotation << std::endl <<
		"Rotations: " << std::endl <<
		std::endl;
	for (int i = 0; i < maxRotation; i++) { //rotation forms
		std::cout << *(rotations + i) << std::endl;
	}
	std::cout << std::endl << "Space:" << std::endl;
	int spaceID = 0;
	for (int w = 0; w < depth; w++) {
		for(int v = 0; v < height; v++) {
			for(int u = 0; u < width; u++) {
				if(*(space + spaceID) == true) std::cout << "#";
				else std::cout << " ";
				spaceID++;
			}
			std::cout << std::endl;
		}
		std::cout << "Layer " << (w+1) << std::endl;
	}

	for (int i = 0; i < width*height*depth; i++) std::cout << *(space + i) << std::endl;
}
	