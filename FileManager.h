#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <sstream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Block.h"
#include "Solver.h"

class FileManager {
private:
	static std::string chooseFile();

public:
	static Block* loadBlock();
	static Block* loadBlock(std::string);
	static Solver* loadPuzzle();

};

#endif