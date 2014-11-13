#ifndef _OBJMESH_H_
#define _OBJMESH_H_

#include "Coordinates.h"
#include <vector>
#include <string>

class OBJMesh
{
public:
	std::vector<Coordinates*> vertices;
	std::vector<Coordinates*> normals;
	std::vector<Coordinates*> UVs;
	std::vector<Indices*> indices;
	//std::vector<std::vector<int>> smoothingGroups;

	std::string materialName;
	std::string textureName;
	std::string objectName;

	int numVerts;
	int numIndices;
	float* vertsArray;
	int* indicesArray;

	void CovertToS3D();
	OBJMesh();
	~OBJMesh();
};

#endif
