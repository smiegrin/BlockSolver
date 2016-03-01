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
	int* rotations;
	int currentRotation;
	int maxRotation;
	bool* space;
public:
	Block();
	Block(int,int,int,int,int*,bool*);

	int getWidth();
	int getHeight();
	int getDepth();
	int getX();
	int getY();
	int getZ();
	int getRotation();
	int getMaxRotation();

	int rotate();

	void printInfo();
	
};

#endif