#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <sstream>
#include <fstream>
#include <Windows.h>
#include "Block.h"

static class FileManager {
private:
	std::string chooseFile();

public:
	Block* loadBlock();

};

#endif