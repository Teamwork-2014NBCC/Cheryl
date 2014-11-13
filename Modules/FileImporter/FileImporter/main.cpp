/********************************************************
* FileImporter
* Imports obj files
* Created by:	Mark Murphy		Date: Oct. 7, 2014
* Modified by:	Mark Murphy		Date: Oct. 14, 2014
*********************************************************/

#include "import_3d.h"
#include <iostream>
#include <windows.h>
#include <GL/gl.h>

//this code sets up memory leak detection
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

void Export(OBJMesh* mesh, std::string fileName)
{
	std::ofstream outfile;
	outfile.open(fileName);


	if (outfile.is_open())
	{
		outfile << mesh->numVerts << std::endl;

		for (int i = 0; i < mesh->numVerts; ++i)
		{
			outfile << mesh->vertsArray[i * 8 + 0] << " ";
			outfile << mesh->vertsArray[i * 8 + 1] << " ";
			outfile << mesh->vertsArray[i * 8 + 2] << " ";
			outfile << mesh->vertsArray[i * 8 + 3] << " ";
			outfile << mesh->vertsArray[i * 8 + 4] << " ";
			outfile << mesh->vertsArray[i * 8 + 5] << " ";
			outfile << mesh->vertsArray[i * 8 + 6] << " ";
			outfile << mesh->vertsArray[i * 8 + 7] << std::endl;
		}


		outfile << mesh->numIndices << std::endl;

		for (int j = 0; j < mesh->numIndices; ++j)
		{
			outfile << mesh->indicesArray[j] << " ";
		}

		outfile << std::endl;
		outfile << mesh->textureName;

		outfile.close();
	}
}

int main(int argc, char* argv[])
{
	//the line below turns on memory leak detection in debug mode
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (argc != 3)
	{
		std::string exe = argv[0];

		while (exe.find("\\", 0) != std::string::npos)
		{ //does the string have a \ in it?
			size_t  pos = exe.find("\\", 0); //store the position of the "\"
			exe.erase(0, pos + 1);          //erase up to it from the source 			
		}

		std::cout << "USAGE: " << exe << " <input OBJ filename> <output S3D filename>" << std::endl;
		system("pause");
		return -1;
	}

	OBJMesh* mesh = new OBJMesh();
	Import* import = new Import(argv[1], mesh);
	mesh->CovertToS3D();

	Export(mesh, argv[2]);

	//system("pause");
	delete import;
	delete mesh;

	return 0;
}