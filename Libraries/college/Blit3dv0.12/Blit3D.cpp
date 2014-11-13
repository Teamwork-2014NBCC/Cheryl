#include "Blit3D.h"

Blit3D::Blit3D(bool fullScreenFlag, float width, float height)
{
	sManager = NULL;
	tManager = NULL;	

	fullScreen = fullScreenFlag;
	screenWidth = width;
	screenHeight = height;
}

void Blit3D::Init()
{
	sManager = new ShaderManager();
	tManager = new TextureManager();

	projectionMatrix = glm::mat4(1.f);
	viewMatrix = glm::mat4(1.f);
}

Blit3D::~Blit3D()
{
	if (tManager) delete tManager;
	if (sManager) delete sManager;
}