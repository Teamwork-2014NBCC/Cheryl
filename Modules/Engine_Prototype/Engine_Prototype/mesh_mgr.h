#ifndef _S3DMESHLOADER_H_
#define _S3DMESHLOADER_H_

#include "S3DMesh.h"
#include "texture_mgr.h"
#include "file_mgr.h"

#include <map>

/******************************************************
* S3DMesh_Manager Class
* Imports S3D file and stores the information withing the class.
* Created by:	Josh Cooper		Date:	Dec. 4, 2014
* Modified by:	Josh Cooper		Date:	Dec. 4, 2014
*******************************************************/
class S3DMesh_Manager
{
	Texture_Manager* txt_mgr = nullptr;
private:
	std::map<std::string, S3DMesh*> mesh_map;
	std::map<std::string, S3DMesh*>::iterator mesh_itor;

	void Load_All(){}
	void Load_Mesh(std::string file, std::string path){}
	S3DMesh* Get_Mesh(std::string file_name){ return nullptr; }
	void Free_Meshes(){}

public:
	S3DMesh_Manager(Texture_Manager* txt_mgr);
	S3DMesh* Import_S3D_File(std::string fileName);
};


#endif
