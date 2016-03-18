#include "Block.h"

Block::Block() {};

Block::Block(int newWidth, int newHeight, int newDepth, int mRot,int *rots, bool*newSpace) {
	width = newWidth;
	height = newHeight;
	depth = newDepth;

	maxRotation = mRot;
	rotations = rots;

	space = newSpace;
	spacePrime = new bool[width*height*depth];

	x = 0;
	y = 0;
	z = 0;
	currentRotation = 0;

	updatePrime();
}

int Block::getWidth() { return widthPrime; }
int Block::getHeight() { return heightPrime; }
int Block::getDepth() { return depthPrime; }
int Block::getX() {return x; }
int Block::getY() { return y; }
int Block::getZ() { return z; }
int Block::getRotation() { return currentRotation; }
int Block::getMaxRotation() { return maxRotation; }

bool Block::colAt(int xCoord, int yCoord, int zCoord) {
	
	if(xCoord > x + widthPrime || xCoord < x ||
		yCoord > y + heightPrime || yCoord < y ||
		zCoord > z + depthPrime || zCoord < z) return false;
		
	else if (*(spacePrime + (xCoord - x)
		+ widthPrime*(yCoord - y)
		+ widthPrime*heightPrime*(zCoord - z))) 
			return true;
}

int Block::rotate() {
	currentRotation++;
	if (currentRotation == maxRotation) currentRotation = 0;
	updatePrime();
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

	//for (int i = 0; i < width*height*depth; i++) std::cout << *(space + i) << std::endl;
}

void Block::setCoordinates(int xCoord, int yCoord, int zCoord) {
	x = xCoord;
	y = yCoord;
	z = zCoord;
}

void Block::updatePrime() {
	int wMark = 0;
	int hMark = 0;
	int dMark = 0;
	switch (*(rotations + currentRotation)) {
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

	if(wMark == 1 || wMark == 2) widthPrime = width, du = &u;
	if(wMark == 3 || wMark == 4) widthPrime = height, du = &v;
	if(wMark == 5 || wMark == 6) widthPrime = depth, du = &w;
	
	if(hMark == 1 || hMark == 2) heightPrime = width, dv = &u;
	if(hMark == 3 || hMark == 4) heightPrime = height, dv = &v;
	if(hMark == 5 || hMark == 6) heightPrime = depth, dv = &w;
	
	if(dMark == 1 || dMark == 2) depthPrime = width, dw = &u;
	if(dMark == 3 || dMark == 4) depthPrime = height, dw = &v;
	if(dMark == 5 || dMark == 6) depthPrime = depth, dw = &w;

	int spaceID;
	for(w = 0; w < depth; w++) {
		for(v = 0; v < height; v++) {
			for(u = 0; u < width; u++) {
				spaceID = 0;
				spaceID += (wMark & 1) ? *du : (widthPrime - 1 - *du);
				spaceID += widthPrime*((hMark & 1) ? *dv : (heightPrime - 1 - *dv));
				spaceID += heightPrime*widthPrime*((dMark & 1) ? *dw : (depthPrime - 1 - *dw));
				*(spacePrime + spaceID) = *(space + u + width*v + width*height*w);
			}
		}
	}

	//#############################
/*
	switch(dMark) {
	case 1:
		switch(hMark) {
		case 3:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 4:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 5:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 6:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		}
		break;
	case 2:
		switch(hMark) {
		case 3:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 4:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 5:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 6:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		}
		break;
	case 3:
		switch(hMark) {
		case 1:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 2:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 5:
			switch(wMark) {
			case 1:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 2:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 6:
			switch(wMark) {
			case 1:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 2:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		}
		break;
	case 4:
		switch(hMark) {
		case 1:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 2:
			switch(wMark) {
			case 5:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 6:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 5:
			switch(wMark) {
			case 1:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 2:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 6:
			switch(wMark) {
			case 1:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 2:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		}
		break;
	case 5:
		switch(hMark) {
		case 1:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 2:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 3:
			switch(wMark) {
			case 1:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 2:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 4:
			switch(wMark) {
			case 1:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 2:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		}
		break;
	case 6:
		switch(hMark) {
		case 1:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			}
			break;
		case 2:
			switch(wMark) {
			case 3:
//				for(int w = 0; w < depth; w++) {
//					for(int v = 0; v < height; v++) {
//						for(int u = 0; u < width; u++) {
//							*(spacePrime + u  v  w ) = *(space + u + v*width + w*width*height);
//						}
//					}
//				}
				break;
			case 4:
				widthPrime = height;
				heightPrime = width;
				depthPrime = depth;
				for(int w = 0; w < depth; w++) {
					for(int v = 0; v < height; v++) {
						for(int u = 0; u < width; u++) {
							*(spacePrime + (widthPrime-1-v) + widthPrime*(widthPrime-1-u) + widthPrime*heightPrime*(depthPrime-1-w)) = *(space + u + v*width + w*width*height);
						}
					}
				}
				break;
			}
			break;
		case 3:
			switch(wMark) {
			case 1:
				widthPrime = width;
				heightPrime = height;
				depthPrime = depth;
				for(int w = 0; w < depth; w++) {
					for(int v = 0; v < height; v++) {
						for(int u = 0; u < width; u++) {
							*(spacePrime + (u) + widthPrime*v + widthPrime*heightPrime*(depthPrime-1-w) ) = *(space + u + v*width + w*width*height);
						}
					}
				}
				break;
			case 2:
				widthPrime = width;
				heightPrime = height;
				depthPrime = depth;
				for(int w = 0; w < depth; w++) {
					for(int v = 0; v < height; v++) {
						for(int u = 0; u < width; u++) {
							*(spacePrime + (widthPrime-1-u) + widthPrime*v + widthPrime*heightPrime*(depthPrime-1-w) ) = *(space + u + v*width + w*width*height);
						}
					}
				}
				break;
			}
			break;
		case 4:
			switch(wMark) {
			case 1:
				widthPrime = width;
				heightPrime = height;
				depthPrime = depth;
				for(int w = 0; w < depth; w++) {
					for(int v = 0; v < height; v++) {
						for(int u = 0; u < width; u++) {
							*(spacePrime + u  + widthPrime*(heightPrime-1-v)  + widthPrime*heightPrime*(depth-1-w)) = *(space + u + v*width + w*width*height);
						}
					}
				}
				break;
			case 2:
				widthPrime = width;
				heightPrime = height;
				depthPrime = depth;
				for(int w = 0; w < depth; w++) {
					for(int v = 0; v < height; v++) {
						for(int u = 0; u < width; u++) {
							*(spacePrime + (widthPrime-1-u) + widthPrime*(heightPrime-1-v) + widthPrime*heightPrime*(depthPrime-1-w)) = *(space + u + v*width + w*width*height);
						}
					}
				}
				break;
			}
			break;
		}
		break;
	}
*/	
	std::cout << std::endl << "Space:" << std::endl;
	spaceID = 0;
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
