#include <Windows.h>
#include <iostream>
#include "FileManager.h"
#include "Block.h"

std::string FileManager::chooseFile() { 
	//Rudimentiry text-based file 
//	std::string filename;
//	std::cout << "Enter Full Filename:" << std::endl;
//	std::getline(std::cin, filename);
//	
//	return filename;
//}
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

	int x, y, z;

	stream.open(filename);
	stream >> x;
	stream >> y;
	stream >> z;
	stream.close();

	return new Block(x,y,z);
}