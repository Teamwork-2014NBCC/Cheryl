#ifndef _S3DMESH_H_
#define _S3DMESH_H_

#include "Blit3D.h"

#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <atomic>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//extern GLFWwindow* window;

//GLOBAL DATA

//glm::mat4 modelMatrix;



class S3DMesh
{
private:
	glm::vec3 Kd; //diffuse reflectivity
	glm::vec3 Ka; //ambient reflectivity
	glm::vec3 Ks; //Specular reflectivity
	GLfloat Shininess; //Specular shininess factor

	GLuint vbo[2];
	GLuint vao = 0;

	glm::vec3 LightIntensity;


	std::string meshName;
	std::string textureName;
	int numVerts;
	int numIndices;
	float* verts;
	int* indices;
	glm::mat4 modelMatrix;
	glm::mat4 rotation_Matrix;
	glm::mat4 translation_Matrix;
	glm::mat4 scale_Matrix;

public:
	void Import(std::string fileName);
	void Update(double milliseconds);
	void Draw(Blit3D *blit3D, GLSLProgram *prog);

	void Transform(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);
	std::string GetTextureName();

	S3DMesh(std::string fileName, Blit3D *blit3D, GLSLProgram *prog);
	~S3DMesh();
};

#endif