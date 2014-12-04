#include "mesh_mgr.h"
#include "global.h"


S3DMesh_Manager::S3DMesh_Manager(Texture_Manager* txt_mgr)
{
	this->txt_mgr = txt_mgr;
}


S3DMesh* S3DMesh_Manager::Import_S3D_File(std::string fileName)
{
	int numVerts;
	int numIndices;
	float* verts;
	int* indices;
	std::string textureName;
	std::string line;

	auto file_map = File_Manager::Get_Files(".s3d");
	auto file_ref = file_map.find(fileName);
	if ( file_ref != file_map.end() )
	{
		std::ifstream infile(file_ref->second + file_ref->first);
		if ( infile.is_open() )
		{
			infile >> line;
			numVerts = atoi(line.c_str());
			verts = new float[numVerts*8];

			for ( int i = 0; i < numVerts * 8; i++ )
			{
				infile >> verts[i];
			}

			infile >> line;
			numIndices = atoi(line.c_str());
			indices = new int[numIndices];
			for ( int i = 0; i < numIndices; i++ )
			{
				infile >> indices[i];
			}

			infile >> line;
			textureName = line;
			infile.close();
			mesh_data info(numVerts, numIndices, verts, indices, textureName);
			S3DMesh* mesh = new S3DMesh(*txt_mgr, get_blit3d()->sManager->UseShader("shader.vert", "shader.frag"), info);
			return mesh;
		}
	}
	return nullptr;
}