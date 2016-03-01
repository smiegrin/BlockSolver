#include <Windows.h>
#include <iostream>
#include "FileManager.h"
#include "Block.h"

std::string FileManager::chooseFile() { 
	// TAKEN FROM: http://www.winprog.org/tutorial/app_two.html
	OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Block Files (*.blk)\0*.blk\0";
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
	std::ifstream stream;

	int x, y, z, maxRotation, *rotations;
	bool* space;

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