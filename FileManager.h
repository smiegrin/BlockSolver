#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <sstream>
#include <fstream>
#include <Windows.h>
#include "Block.h"

class FileManager {
private:
	static std::string chooseFile();

public:
	static Block* loadBlock();

};

#endif