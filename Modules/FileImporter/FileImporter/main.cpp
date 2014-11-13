/********************************************************
* FileImporter
* Imports obj files
* Created by:	Mark Murphy		Date: Oct. 7, 2014
* Modified by:	Mark Murphy		Date: Oct. 14, 2014
*********************************************************/

#include "import_3d.h"

//this code sets up memory leak detection
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

void main()
{
	OBJMesh* mesh = new OBJMesh();
	Import* import = new Import("box.obj", mesh);
	system("pause");
	delete import;
	delete mesh;
}