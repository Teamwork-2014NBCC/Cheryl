/*
Example program that shows Blit3D is working
*/
#include "S3DMesh.h"


Blit3D *blit3D = NULL;

//GLOBAL DATA
GLSLProgram *prog = NULL;

std::atomic<float> angle = 0;

//used for scroll wheel test
std::atomic<int> scroll = 0;

//used for joystick test
std::mutex joystickMutex;
B3D::JoystickState joystickState;
int joystickNumber;
float joystickTestPositionAxis1 = 0.f;
float joystickTestPositionAxis2 = 0.f;
float joystickTestPositionAxis4 = 0.f;
float joystickTestPositionAxis5 = 0.f;
bool foundJoystick = false;

S3DMesh* mesh_Cannon = NULL;
S3DMesh* mesh_Hull = NULL;
S3DMesh* mesh_Turret = NULL;
S3DMesh* mesh_Wheel = NULL;
S3DMesh* mesh_Box = NULL;

void Init()
{
	blit3D->SetMode(Blit3DRenderMode::BLIT3D);

	prog = blit3D->sManager->UseShader("shader.vert", "shader.frag"); //load/compile/link

	//lighting variables
	glm::vec3 LightPosition = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 LightIntensity = glm::vec3(0.4f, 1.0f, 0.0f);

	//send lighting info to the shader
	prog->setUniform("LightPosition", LightPosition);
	prog->setUniform("LightIntensity", LightIntensity);

	//send matrices to the shader
	prog->setUniform("projectionMatrix", blit3D->projectionMatrix);
	prog->setUniform("viewMatrix", blit3D->viewMatrix);

	mesh_Cannon = new S3DMesh("APC_Cannon.S3D", blit3D, prog, false);
	mesh_Hull = new S3DMesh("APC_Hull.S3D", blit3D, prog, false);
	mesh_Turret = new S3DMesh("APC_Turret.S3D", blit3D, prog, false);
	mesh_Wheel = new S3DMesh("APC_Wheel.S3D", blit3D, prog, false);
	mesh_Box = new S3DMesh("box.S3D", blit3D, prog, true);

	blit3D->projectionMatrix *= glm::perspective(45.0f, (GLfloat)(blit3D->screenWidth) / (GLfloat)(blit3D->screenHeight), 0.1f, 10000.0f);



	//NEVER call CheckJoystick()/ PollJoystick() from Update if not running Blit3DThreadModel::SINGLETHREADED, or any other thread you spawn.
	//If you lose a joystick or just want to add another, call CheckJoystick()/ PollJoystick() from a callback
	//DoJoystick() function to setup/resetup a joystick. 

	//check for joysticks, stop at first joystick found plugged in
	for (joystickNumber = 1; joystickNumber <= 8; ++joystickNumber)
	{
		if (blit3D->CheckJoystick(joystickNumber))
		{
			foundJoystick = true;
			break;
		}
	}

	if (foundJoystick)
	{
		//get the state arrays for this joystick
		if (!blit3D->PollJoystick(joystickNumber, joystickState)) foundJoystick = false;
	}
}

void DeInit(void)
{
	if (blit3D) delete blit3D;
	delete mesh_Cannon;
	delete mesh_Hull;
	delete mesh_Turret;
	delete mesh_Wheel;
	delete mesh_Box;
}

void Update(double seconds)
{
	angle = angle + static_cast<float>(seconds)* 30;
	while (angle > 360) angle = angle - 360;
	mesh_Cannon->Update(seconds);
	mesh_Hull->Update(seconds);
	mesh_Turret->Update(seconds);
	mesh_Wheel->Update(seconds);
	mesh_Box->Update(seconds);
}

void Draw(void)
{
	glClearColor(0.8f, 0.6f, 0.7f, 0.0f);	//clear colour: r,g,b,a 	
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	blit3D->SetMode(Blit3DRenderMode::BLIT3D);


	glm::vec3 LightIntensity = glm::vec3(1.0f, 1.0f, 1.0f);
	prog->setUniform("LightIntensity", LightIntensity);

	mesh_Cannon->Scale(1.0f, 1.0f, 1.0f);
	mesh_Cannon->Transform(-10, 0, -20.0f + scroll);
	mesh_Cannon->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Hull->Scale(1.0f, 1.0f, 1.0f);
	mesh_Hull->Transform(-5, 0, -20.0f + scroll);
	mesh_Hull->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Turret->Scale(1.0f, 1.0f, 1.0f);
	mesh_Turret->Transform(0, 0, -20.0f + scroll);
	mesh_Turret->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Wheel->Scale(1.0f, 1.0f, 1.0f);
	mesh_Wheel->Transform(5, 0, -20.0f + scroll);
	mesh_Wheel->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Box->Scale(1.0f, 1.0f, 1.0f);
	mesh_Box->Transform(10, 0, -20.0f + scroll);
	mesh_Box->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Cannon->Draw(blit3D, prog);
	mesh_Hull->Draw(blit3D, prog);
	mesh_Turret->Draw(blit3D, prog);
	mesh_Wheel->Draw(blit3D, prog);
	mesh_Box->Draw(blit3D, prog);

	glBindVertexArray(0);//turn off vao again
	//glfwSwapBuffers(window);
}

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
void DoInput(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		blit3D->Quit(); //start the shutdown sequence
}

void DoCursor(double x, double y)
{
	//cx = (float)x;
	//cy = blit3D->screenHeight - (float)y;
}

void DoMouseButton(int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	//{
	//	spriteSize2 = 0.5f;
	//}
	//else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	//{
	//	spriteSize2 = 2.0f;
	//}
	//else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	//{
	//	spriteSize1 = 0.5f;
	//}
	//else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	//{
	//	spriteSize1 = 2.0f;
	//}
	//else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	//{
	//	/*	WARNING
	//	DON'T DO THIS WITH ATOMICS:

	//	spriteSize1 = spriteSize2 = 4.f;

	//	It probably won't do what you want it to do; instead, set each atomic individually, like below.
	//	*/
	//	spriteSize1 = 4.f;
	//	spriteSize2 = 4.f;
	//}
	//else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	//{
	//	spriteSize1 = 2.f;
	//	spriteSize2 = 2.f;
	//}
}

void DoScrollwheel(double xoffset, double yoffset)
{
	//A simple mouse wheel, being vertical, provides offsets along the Y-axis.
	if (yoffset > 0)
	{
		//scrolled up
		scroll++;
		if (scroll > 100) scroll = 100;
	}
	else if (yoffset < 0)
	{
		//scrolled down
		scroll--;
		if (scroll < -100) scroll = -100;
	}
}

void DoJoystick(void)
{
	if (foundJoystick)
	{

		if (blit3D->PollJoystick(joystickNumber, joystickState))
		{
			//joystick at joystickNumber is still plugged in, so we can work with it's states
			joystickMutex.lock();
			//axis states are between -1.f and 1.f
			if (joystickState.axisCount > 0) joystickTestPositionAxis1 = joystickState.axisStates[0] * 100.f;
			if (joystickState.axisCount > 1) joystickTestPositionAxis2 = joystickState.axisStates[1] * -100.f;
			if (joystickState.axisCount > 3) joystickTestPositionAxis4 = joystickState.axisStates[3] * -100.f;
			if (joystickState.axisCount > 4) joystickTestPositionAxis5 = joystickState.axisStates[4] * 100.f;

			if (joystickState.buttonCount > 6)
			{
				//pressing BACK button will exit the program
				if (joystickState.buttonStates[6] == GLFW_PRESS) blit3D->Quit(); //start the shutdown sequence
			}
			joystickMutex.unlock();
		}
		else foundJoystick = false;
	}
	else
	{
		//search for a joystick again
		joystickMutex.lock();
		//check for joysticks, stop at first joystick found plugged in
		for (joystickNumber = 1; joystickNumber <= 8; ++joystickNumber)
		{
			if (blit3D->CheckJoystick(joystickNumber))
			{
				foundJoystick = true;
				break;
			}
		}

		if (foundJoystick)
		{
			//get the state arrays for this joystick
			if (!blit3D->PollJoystick(joystickNumber, joystickState)) foundJoystick = false;
		}

		joystickMutex.unlock();
	}
}

int main(int argc, char *argv[])
{
	blit3D = new Blit3D(Blit3DWindowModel::BORDERLESSFULLSCREEN, 1280, 720);

	//set our callback funcs
	blit3D->SetInit(Init);
	blit3D->SetDeInit(DeInit);
	blit3D->SetUpdate(Update);
	blit3D->SetDraw(Draw);
	blit3D->SetDoInput(DoInput);
	blit3D->SetDoCursor(DoCursor);
	blit3D->SetDoMouseButton(DoMouseButton);
	blit3D->SetDoScrollwheel(DoScrollwheel);
	blit3D->SetDoJoystick(DoJoystick);

	//Run() blocks until the window is closed
	blit3D->Run(Blit3DThreadModel::SIMPLEMULTITHREADED);

}