#ifndef _IMPORT_3D_H_
#define _IMPORT_3D_H_

#include "OBJMesh.h"
#include <fstream>
#include <vector>
#include <string>
/********************************************************
* Import
* Imports obj files
* Created by:	Mark Murphy		Date: Oct. 7, 2014
* Modified by:	Mark Murphy		Date: Oct. 7, 2014
*********************************************************/
class Import
{
public:
	int lineCount;
	bool hasIndices, timeToExit;
	Import(std::string fileName, OBJMesh* mesh);
	~Import();
private:
};

#endif