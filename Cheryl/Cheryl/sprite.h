#include <blit3d/Blit3D.h>

class graphic
{
private:
	GLuint vboId;	// ID of VBO
	GLuint vaoId;	//ID of the VAO 		

	glm::mat4 modelMatrix; // Store the model matrix 
	int modelMatrixLocation; // Store the location of our model matrix in the shader
	int alphaLocation; //store the location of the alpha variable in the shader

public:
	GLfloat dest_x; //window coordinates of the center of the sprite, in pixels
	GLfloat dest_y;
	GLfloat angle; //angle of the sprite, in degrees
	GLfloat alpha; //amount of extra alpha-blending to apply, modifies opacity of the sprite
	GLfloat scale; //scaling value, 1 = 100%, 0.5 = half size, etc.
};