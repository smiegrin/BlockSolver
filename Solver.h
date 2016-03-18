#ifndef SOLVER_H
#define SOLVER_H



class Solver {
	BlockStack blocks;
	Block* currentBlock;
	

public:
	Block* getCurrentBlock();
	void step();
}

#endif
