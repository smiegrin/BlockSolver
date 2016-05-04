#include "Block.h"

//default constructor. Not recomended for use.
Block::Block() {};

//standard constructor.
//newWidth: the width of the block to be constructed
//newHeight: the height of the block to be constructed
//newDepth, the depth of the block to be constructed
//mRot, the number of unique rotations the block has.
//*rots, the address of the first element in an array of rotation indicies of size (mRot)
//*newSpace, the address of the first element in an array to represent the space occupied by the block of size (newWidth*newHeight*newDepth)
Block::Block(int newWidth, int newHeight, int newDepth, int mRot,int *rots, bool*newSpace) {
	//initialize size
	width = newWidth;
	height = newHeight;
	depth = newDepth;

	//initialize rotations
	maxRotation = mRot;
	rotations = rots;

	//initialize space
	space = newSpace;
	spacePrime = new bool[width*height*depth];

	//initialize position
	x = 0;
	y = 0;
	z = 0;
	currentRotation = 0;

	//establish original orientation
	updatePrime();
}

//accesor methods
int Block::getWidth() { return widthPrime; }
int Block::getHeight() { return heightPrime; }
int Block::getDepth() { return depthPrime; }
int Block::getX() { return x; }
int Block::getY() { return y; }
int Block::getZ() { return z; }
int Block::getRotation() { return currentRotation; }
int Block::getMaxRotation() { return maxRotation; }

//Returns TRUE if the block occupies the given grid space in absolute 3-dimensional coordinates (xCoord,yCoord,zCoord)
bool Block::colAt(int xCoord, int yCoord, int zCoord) {
	//false if coordinate is beyond bounds of block
	if(xCoord >= x + widthPrime || xCoord < x ||
		yCoord >= y + heightPrime || yCoord < y ||
		zCoord >= z + depthPrime || zCoord < z) return false;
	//ortherwise returns the truth of occupation	
	else return *(spacePrime + (xCoord - x)
		+ widthPrime*(yCoord - y)
		+ widthPrime*heightPrime*(zCoord - z));
}

//causes the block to advance to its next designated rotation
//causes the block to return to its original orientation should it rotate past its last orientation
//retuns the new rotation reference of the block, 0 if it has returned to its original orientation
int Block::rotate() {
	currentRotation++;
	if (currentRotation == maxRotation) currentRotation = 0;
	updatePrime();//update the space member for new rotation
	return currentRotation;
}

//debuging function used to list information from the block
//lists:
//-dimensions
//-rotations
//-leveled layout of block's current space in current orientation
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
	for (int w = 0; w < depthPrime; w++) {
		for(int v = 0; v < heightPrime; v++) {
			for(int u = 0; u < widthPrime; u++) {
				if(*(spacePrime + spaceID) == true) std::cout << "#";
				else std::cout << " ";
				spaceID++;
			}
			std::cout << std::endl;
		}
		std::cout << "Layer " << (w+1) << std::endl;
	}
}

//moves the block to a given absolute coordinate, (xCoord, yCoord, zCoord)
void Block::setCoordinates(int xCoord, int yCoord, int zCoord) {
	x = xCoord;
	y = yCoord;
	z = zCoord;
}

//internal fucntion used to update the meber "spacePrime" of block for use as the current orientation of the block
void Block::updatePrime() {
	int wMark = 0;
	int hMark = 0;
	int dMark = 0;
	switch (*(rotations + currentRotation)) { //establishes variables to mark the order and direction to traverse the three dimensions of the space array based on currentRotation.
	//order listed in additional documentation
	case 0:
		wMark = 1;
		hMark =3;
		dMark = 5;
		break;
	case 1:
		wMark = 1;
		hMark =4;
		dMark = 5;
		break;
	case 2:
		wMark = 2;
		hMark =4;
		dMark = 5;
		break;
	case 3:
		wMark = 2;
		hMark =3;
		dMark = 5;
		break;
	case 4:
		wMark = 3;
		hMark =2;
		dMark = 5;
		break;
	case 5:
		wMark = 4;
		hMark =2;
		dMark = 5;
		break;
	case 6:
		wMark = 4;
		hMark =1;
		dMark = 5;
		break;
	case 7:
		wMark = 3;
		hMark =1;
		dMark = 5;
		break;
	case 8:
		wMark = 3;
		hMark =1;
		dMark = 6;
		break;
	case 9:
		wMark = 3;
		hMark =2;
		dMark = 6;
		break;
	case 10:
		wMark = 4;
		hMark =2;
		dMark = 6;
		break;
	case 11:
		wMark = 4;
		hMark =1;
		dMark = 6;
		break;
	case 12:
		wMark = 1;
		hMark =4;
		dMark = 6;
		break;
	case 13:
		wMark = 2;
		hMark =4;
		dMark = 6;
		break;
	case 14:
		wMark = 2;
		hMark =3;
		dMark = 6;
		break;
	case 15:
		wMark = 1;
		hMark =3;
		dMark = 6;
		break;
	case 16:
		wMark = 1;
		hMark =6;
		dMark = 3;
		break;
	case 17:
		wMark = 1;
		hMark =5;
		dMark = 3;
		break;
	case 18:
		wMark = 2;
		hMark =5;
		dMark = 3;
		break;
	case 19:
		wMark = 2;
		hMark =6;
		dMark = 3;
		break;
	case 20:
		wMark = 6;
		hMark =2;
		dMark = 3;
		break;
	case 21:
		wMark = 5;
		hMark =2;
		dMark = 3;
		break;
	case 22:
		wMark = 5;
		hMark =1;
		dMark = 3;
		break;
	case 23:
		wMark = 6;
		hMark =1;
		dMark = 3;
		break;
	case 24:
		wMark = 5;
		hMark =2;
		dMark = 4;
		break;
	case 25:
		wMark = 5;
		hMark =1;
		dMark = 4;
		break;
	case 26:
		wMark = 6;
		hMark =1;
		dMark = 4;
		break;
	case 27:
		wMark = 6;
		hMark =2;
		dMark = 4;
		break;
	case 28:
		wMark = 2;
		hMark =6;
		dMark = 4;
		break;
	case 29:
		wMark = 1;
		hMark =6;
		dMark = 4;
		break;
	case 30:
		wMark = 1;
		hMark =5;
		dMark = 4;
		break;
	case 31:
		wMark = 2;
		hMark =5;
		dMark = 4;
		break;
	case 32:
		wMark = 3;
		hMark =5;
		dMark = 1;
		break;
	case 33:
		wMark = 3;
		hMark =6;
		dMark = 1;
		break;
	case 34:
		wMark = 4;
		hMark =6;
		dMark = 1;
		break;
	case 35:
		wMark = 4;
		hMark =5;
		dMark = 1;
		break;
	case 36:
		wMark = 5;
		hMark =4;
		dMark = 1;
		break;
	case 37:
		wMark = 6;
		hMark =4;
		dMark = 1;
		break;
	case 38:
		wMark = 6;
		hMark =3;
		dMark = 1;
		break;
	case 39:
		wMark = 5;
		hMark =3;
		dMark = 1;
		break;
	case 40:
		wMark = 5;
		hMark =3;
		dMark = 2;
		break;
	case 41:
		wMark = 5;
		hMark =4;
		dMark = 2;
		break;
	case 42:
		wMark = 6;
		hMark =4;
		dMark = 2;
		break;
	case 43:
		wMark = 6;
		hMark =3;
		dMark = 2;
		break;
	case 44:
		wMark = 3;
		hMark =6;
		dMark = 2;
		break;
	case 45:
		wMark = 4;
		hMark =6;
		dMark = 2;
		break;
	case 46:
		wMark = 4;
		hMark =5;
		dMark = 2;
		break;
	case 47:
		wMark = 3;
		hMark =5;
		dMark = 2;
		break;
	}

	//#############################
	int w = 0;
	int v = 0;
	int u = 0;
	int* dw = 0;
	int* dv = 0;
	int* du = 0;

	if(wMark == 1 || wMark == 2) widthPrime = width, du = &u;//bind spacePrime x to x
	if(wMark == 3 || wMark == 4) widthPrime = height, du = &v;//bind spacePrime x to y
	if(wMark == 5 || wMark == 6) widthPrime = depth, du = &w;//bind spacePrime x to z
	
	if(hMark == 1 || hMark == 2) heightPrime = width, dv = &u;//bind spacePrime y to x
	if(hMark == 3 || hMark == 4) heightPrime = height, dv = &v;//bind spacePrime y to y
	if(hMark == 5 || hMark == 6) heightPrime = depth, dv = &w;//bind spacePrime y to z
	
	if(dMark == 1 || dMark == 2) depthPrime = width, dw = &u;//bind spacePrime z to x
	if(dMark == 3 || dMark == 4) depthPrime = height, dw = &v;//bind spacePrime z to y
	if(dMark == 5 || dMark == 6) depthPrime = depth, dw = &w;//bind spacePrime z to z

	int spaceID;
	for(w = 0; w < depth; w++) {//traverse depth
		for(v = 0; v < height; v++) {//traverse height
			for(u = 0; u < width; u++) {//traverse width
				spaceID = 0;
				spaceID += (wMark & 1) ? *du : (widthPrime - 1 - *du);//navigate allong rows
				spaceID += widthPrime*((hMark & 1) ? *dv : (heightPrime - 1 - *dv));//navigate allong columns
				spaceID += heightPrime*widthPrime*((dMark & 1) ? *dw : (depthPrime - 1 - *dw));// navigate ammong layers
				*(spacePrime + spaceID) = *(space + u + width*v + width*height*w);//trasfer value from space variable to the proper spacePrime adress
			}
		}
	}
}
