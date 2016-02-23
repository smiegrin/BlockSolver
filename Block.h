#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>

class Block{
private:
	int width;
	int height;
	int depth;
	int x;
	int y;
	int z;
	int* space;
	int rotation;
	int maxRotation;
public:
	Block();
	Block(int,int,int);

	int getWidth();
	int getHeight();
	int getDepth();
	int getX();
	int getY();
	int getZ();
	int getRotation();
	int getMaxRotation();

	int rotate();
	
};

#endif