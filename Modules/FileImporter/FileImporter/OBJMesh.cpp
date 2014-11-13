#include "OBJMesh.h"

OBJMesh::OBJMesh()
{
	numVerts = 0;
	numIndices = 0;
}

void OBJMesh::CovertToS3D()
{
	if (numIndices != 0 || numVerts != 0)
	{
		numVerts = 0;
		numIndices = 0;
		delete[] vertsArray;
		delete[] indicesArray;
	}

	numIndices = indices.size();
	numVerts = numIndices;

	indicesArray = new int[numIndices];
	vertsArray = new float[numVerts*8];

	for (int i = 0; i < indices.size(); i++)
	{
		vertsArray[i * 8 + 0] = indices[i]->vertices->x;
		vertsArray[i * 8 + 1] = indices[i]->vertices->y;
		vertsArray[i * 8 + 2] = indices[i]->vertices->z;
		vertsArray[i * 8 + 3] = indices[i]->normals->x;
		vertsArray[i * 8 + 4] = indices[i]->normals->y;
		vertsArray[i * 8 + 5] = indices[i]->normals->z;
		vertsArray[i * 8 + 6] = indices[i]->UVs->x;
		vertsArray[i * 8 + 7] = indices[i]->UVs->y;
		indicesArray[i] = indices[i]->index;
	}
}

OBJMesh::~OBJMesh()
{
	for (int i = vertices.size() - 1; i >= 0; i--)
	{
		delete vertices[i];
	}
	vertices.clear();
	for (int i = normals.size() - 1; i >= 0; i--)
	{
		delete normals[i];
	}
	normals.clear();
	for (int i = UVs.size() - 1; i >= 0; i--)
	{
		delete UVs[i];
	}
	UVs.clear();
	for (int i = indices.size() - 1; i >= 0; i--)
	{
		delete indices[i];
	}
	indices.clear();

	//smoothingGroups.clear();

	delete[] vertsArray;
	delete[] indicesArray;
}