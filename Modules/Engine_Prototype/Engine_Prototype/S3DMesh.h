#ifndef _S3DMESH_H_
#define _S3DMESH_H_

#include <blit3d/Blit3D.h>

#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <atomic>
#include "texture_mgr.h"
//#include "file_mgr.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

extern GLFWwindow* window;

//GLOBAL DATA

//glm::mat4 modelMatrix;

struct mesh_data
{
	int numVerts = 0;
	int numIndices = 0;
	float* verts = nullptr;
	int* indices = nullptr;
	std::string textureName;

	mesh_data(){}
	mesh_data( int nv, int ni, float* verts, int* indices, std::string tx )
	{
		numVerts = nv;
		numIndices = ni;
		this->verts = verts;
		this->indices = indices;
		textureName = tx;
	}
	mesh_data( const mesh_data& ref )
	{
		numVerts = ref.numVerts;
		numIndices = ref.numIndices;
		this->verts = ref.verts;
		this->indices = ref.indices;
		textureName = ref.textureName;
	}
};

/******************************************************
* S3DMesh Class
* Stores the S3D information within the class.
* Created by:	Mark Murphy		Date:	Oct. 8, 2014
* Modified by:	Josh Cooper		Date:	Dec. 4, 2014
*******************************************************/
class S3DMesh
{
private:
	GLSLProgram *prog = nullptr;

	glm::vec3 Kd; //diffuse reflectivity
	glm::vec3 Ka; //ambient reflectivity
	glm::vec3 Ks; //Specular reflectivity
	GLfloat Shininess; //Specular shininess factor

	GLuint vbo[2];
	GLuint vao = 0;

	texid texID;

	mesh_data info;
	int		&numVerts = info.numVerts;
	int		&numIndices = info.numIndices;
	float*	&verts = info.verts;
	int*		&indices = info.indices;
	std::string &textureName = info.textureName;
	//Deprecated Properties
	/*
	glm::mat4 modelMatrix;
	glm::mat4 rotation_Matrix;
	glm::mat4 translation_Matrix;
	glm::mat4 scale_Matrix;*/

public:
	bool bStripped;
	S3DMesh( GLSLProgram* prog, mesh_data info, bool isStripped = true );
	~S3DMesh();
	void Import( std::string fileName );
	void Update( double milliseconds );
	void Draw( glm::mat4 modelMatrix );

	//Deprecated Methods
	/*
	void Transform(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);*/
};

#endif