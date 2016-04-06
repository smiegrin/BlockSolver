#include <Windows.h>
#include <iostream>
#include <string>
#include "FileManager.h"
#include "Block.h"
#include "Board.h"
#include "Solver.h"

std::string FileManager::chooseFile() { 
	// TAKEN FROM: http://www.winprog.org/tutorial/app_two.html
	OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Puzzle Files (*.pzl)\0*.pzl\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    if(GetOpenFileName(&ofn))
    {
		return szFileName;
        // Do something usefull with the filename stored in szFileName 
    }
	return NULL;
}

Block* FileManager::loadBlock() {
	std::string filename = chooseFile();
	if (filename == "") return NULL;

	return loadBlock(filename);
}

Block* FileManager::loadBlock(std::string filename) {
	int x, y, z, maxRotation, *rotations;
	bool* space;
	std::ifstream stream;

	stream.open(filename);

	//size
	stream >> x;
	stream >> y;
	stream >> z;

	//rotations
	stream >> maxRotation;
	rotations = new int[maxRotation];
	for (int i = 0; i < maxRotation; i++) stream >> *(rotations + i);

	//space
	space = new bool[x*y*z];
	char temp = 'x';
	for (int i = 0; i < x*y*z; i ++) {
		stream >> temp;
		while(temp == '\n') stream >> temp;
		if (temp == 'X') *(space + i) = true;
		else *(space + i) = false;
	}

	stream.close();

	return new Block(x,y,z,maxRotation,rotations,space);
}

Solver* FileManager::loadPuzzle() {
	std::string filename = chooseFile();
	if (filename == "") return NULL;

	int x, y, z, numOfBlocks;
	Board* board;
	Block* blocks;
	std::ifstream stream;
	stream.open(filename);

	//board size
	stream >> x;
	stream >> y;
	stream >> z;

	//space
	bool* space = new bool[x*y*z];
	char temp = 'x';
	for (int i = 0; i < x*y*z; i ++) {
		stream >> temp;
		while(temp == '\n') stream >> temp;
		if (temp == 'X') *(space + i) = true;
		else *(space + i) = false;
	}
	board = new Board(x,y,z,space);

	//blocks

	stream >> numOfBlocks;
	blocks = new Block[numOfBlocks];

	std::ifstream blockStream;

	int i = filename.size() - 1;
	while (filename.at(i) != '\\') {
		i--;
	}
	filename.assign(filename.c_str(),i + 1);
	std::cout << filename << std::endl;

	std::string blockName = "";
	for (int i = 0; i < numOfBlocks; i++) {
		std::getline(stream, blockName);
		if (blockName == "") std::getline(stream, blockName);
		std::cout << filename + blockName + ".blk" << std::endl;
		*(blocks + i) = *FileManager::loadBlock(filename + blockName + ".blk");
	}

	stream.close();


	return new Solver(board, blocks, numOfBlocks);
}