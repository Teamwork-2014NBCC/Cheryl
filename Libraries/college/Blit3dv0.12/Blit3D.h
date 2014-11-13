/* Blit3D cross-platform game graphics library, written by Darren Reid

version 0.11
*/


#ifndef _BLIT3D_H_
#define _BLIT3D_H_

#ifdef _WIN32
	#define WIN32_EXTRA_LEAN
	#include <Windows.h>
#endif
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <glm/glm.hpp> //GLM OpenGL math library
#include <glm/gtc/type_ptr.hpp> //used to covert glm data to OpenGL data
#include <glm/gtc/quaternion.hpp> //quaternions for handling rotation
#include < glm/gtc/matrix_transform.hpp > //transformation functiona ala OpenGL

#include "TextureManager.h"
#include "ShaderManager.h"

class Blit3D
{
public:
	ShaderManager *sManager;
	TextureManager *tManager;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	float screenWidth, screenHeight;
	bool fullScreen;

	Blit3D(bool fullScreenFlag, float width, float height);
	~Blit3D();
	void Init();
};

#endif