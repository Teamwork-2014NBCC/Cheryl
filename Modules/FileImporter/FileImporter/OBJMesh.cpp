#include "OBJMesh.h"

OBJMesh::OBJMesh()
{
}

OBJMesh::~OBJMesh()
{
	for (int i = vertices.size() - 1; i > 0; i--)
	{
		delete vertices[i];
	}
	vertices.clear();
	for (int i = normals.size() - 1; i > 0; i--)
	{
		delete normals[i];
	}
	normals.clear();
	for (int i = UVs.size() - 1; i > 0; i--)
	{
		delete UVs[i];
	}
	UVs.clear();
	for (int i = indices.size() - 1; i > 0; i--)
	{
		delete indices[i];
	}
	indices.clear();
}