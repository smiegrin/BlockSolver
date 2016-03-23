#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>

class Block{
private:
	int width;
	int widthPrime;
	int height;
	int heightPrime;
	int depth;
	int depthPrime;
	int x;
	int y;
	int z;
	int* rotations;
	int currentRotation;
	int maxRotation;
	bool* space;
	bool* spacePrime;

	void updatePrime();
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
	bool colAt(int,int,int);

	int rotate();
	void setCoordinates(int,int,int);

	void printInfo();
	
};

#endif