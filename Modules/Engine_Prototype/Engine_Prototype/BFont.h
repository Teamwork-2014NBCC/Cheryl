#ifndef _BFONT_H_
#define _BFONT_H_

#include <blit3d/Blit3D.h>

class BFont
{
	B3D::TVertex *verts;  // memory for vertice data
	GLuint vboId;	// ID of VBO
	GLuint vaoId;	//ID of the VAO 		

	GLuint texId; //ID of texture
	std::string textureName; //filename of the texture
	TextureManager *texManager; //pointer to the global texture manager
	glm::mat4 modelMatrix; // Store the model matrix 
	int modelMatrixLocation; // Store the location of our model matrix in the shader
	int alphaLocation; //store the location of the alpha variable in the shader	//-Fréderic Duguay
	float fontSize;
	int widths[256];
	GLSLProgram *prog; //our shader for 2d rendering

public:
	GLfloat dest_x; //window coordinates of the center of the sprite, in pixels
	GLfloat dest_y;
	GLfloat angle; //angle of the sprite, in degrees
	GLfloat alpha;//-Fréderic Duguay
	BFont(std::string TextureFileName, std::string widths_file, float fontsize, TextureManager *TexManager, GLSLProgram *shader);

	void DrawText(bool whichFont, float x, float y, std::string output); //draws the string
	float WidthText(bool whichFont, std::string output);//returns the width of the text string, in pixels
	~BFont(void);
};

#endif