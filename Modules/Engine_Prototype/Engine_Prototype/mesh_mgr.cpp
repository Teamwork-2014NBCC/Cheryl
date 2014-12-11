#include "mesh_mgr.h"
#include "global.h"

void S3DMesh_Manager::Init()
{
}

void S3DMesh_Manager::Load_All()
{
	// prefix sl for string local type
	using slFile_Name = std::string;
	using slFile_Path = std::string;
	Init();
	std::map<slFile_Name, slFile_Path> path_map = File_Manager::Get_Files( ".s3d" );
	std::map<slFile_Name, slFile_Path>::iterator path_itor = path_map.begin();
	for ( ; path_itor != path_map.end(); ++path_itor )
	{
		if ( mesh_map.find( path_itor->first ) == mesh_map.end() )
		{
			Load_Mesh( path_itor->first, path_itor->second );
		}
	}
}

void S3DMesh_Manager::Load_Mesh( std::string file, std::string path )
{
	S3DMesh* mesh = Import_S3D_File( path + file );
	if ( mesh )
	{
		mesh_map.emplace( file, std::make_pair( 0, mesh ) );
	}
}

S3DMesh* S3DMesh_Manager::Import_S3D_File( std::string filepath )
{
	int numVerts;
	int numIndices;
	float* verts;
	int* indices;
	std::string textureName;
	std::string line;

	std::ifstream infile( filepath );
	if ( infile.is_open() )
	{
		infile >> line;
		numVerts = atoi( line.c_str() );
		verts = new float[numVerts*8];

		for ( int i = 0; i < numVerts * 8; i++ )
		{
			infile >> verts[i];
		}

		infile >> line;
		numIndices = atoi( line.c_str() );
		indices = new int[numIndices];
		for ( int i = 0; i < numIndices; i++ )
		{
			infile >> indices[i];
		}

		infile >> line;
		textureName = line;
		infile.close();
		mesh_data info( numVerts, numIndices, verts, indices, textureName );
		S3DMesh* mesh = new S3DMesh( get_blit3d()->sManager->UseShader( "shader.vert", "shader.frag" ), info );
		return mesh;
	}
	return nullptr;
}

S3DMesh* S3DMesh_Manager::Get_Mesh( std::string file_name )
{
	mesh_itor = mesh_map.find( file_name );
	if ( mesh_itor != mesh_map.end() )
	{
		mesh_itor->second.first++;
		return mesh_itor->second.second;
	}
	return nullptr;
}

void S3DMesh_Manager::Free_Mesh( std::string file_name)
{
	mesh_itor = mesh_map.find( file_name );
	if ( mesh_itor != mesh_map.end() )
	{
		if ( --( mesh_itor->second.first ) == 0 )
		{
			delete mesh_itor->second.second;
			mesh_itor->second.second = nullptr;
			//clear the mesh from the std::map
			mesh_map.erase( mesh_itor );
		}
	}
}