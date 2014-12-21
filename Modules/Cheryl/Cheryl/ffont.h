#ifndef _FONT_HANDLER_H_
#define _FONT_HANDLER_H_

#include <blit3d/Blit3D.h>

class FFont
{
	B3D::TVertex *verts;  // memory for vertice data
	GLuint vboId;	// ID of VBO
	GLuint vaoId;	//ID of the VAO

	GLuint texID; //ID of texture
	std::string textureName; //filename of the texture,
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
	FFont( std::string TextureFileName, std::string widths_file, float fontsize, GLSLProgram *shader );

	void DrawTxt( bool whichFont, float x, float y, std::string output ); //draws the string
	float WidthText( bool whichFont, std::string output );//returns the width of the text string, in pixels
	~FFont( void );
};

class Font_Handler
{
private:
	FFont *ffont = nullptr;
	float fontSize;

public:
	void Write( bool otherFont, int x, int y, std::string s );
	void ChangeFontSize( float newSize );

	Font_Handler( float fSize = 18 );
	~Font_Handler();
};

#endif