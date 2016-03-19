#ifndef BOARD_H
#define BOARD_H

class Board {
	int height, width, depth;
	bool* space;

public:
	Board(int,int,int,bool*);
	bool colAt(int,int,int);
	int getWidth();
	int getHeight();
	int getDepth();
};

#endif