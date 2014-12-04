#include <blit3d\Blit3D.h>
#include <debug_toolset.h>

#include <atomic>
#include <stdio.h>
#include <conio.h>
#include <thread>

#include "Player.h"
#include "game.h"
#include "global.h"

#ifdef _WIN32
	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <crtdbg.h>
		#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
		#define new DEBUG_NEW
	#endif
#endif



Blit3D* get_blit3d()
{
	static Blit3D* the_blit3D = new Blit3D(Blit3DWindowModel::DECORATEDWINDOW, 1280, 720);
	return the_blit3D;
}

game& get_game_engine()
{
	static game engine;
	return engine;
}

void Init()
{
	get_game_engine().Init();
}
void DeInit()
{
	get_game_engine().DeInit();
}
void Update(double seconds)
{
	get_game_engine().Update(seconds);
}
void Draw()
{	
	get_game_engine().Draw();
}
void DoInput(int key, int scancode, int action, int mods)
{
	get_game_engine().DoInput(key, scancode, action, mods);
}
void DoCursor(double x, double y)
{
	get_game_engine().DoCursor(x, y);
}

inline void game::Init()
{
	dbg::FileLog_Mgr::Start();

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//load sprites


	//load a font set
	font = new Font_Handler(get_blit3d(),48.0f);

	this->player = new Player();
	this->combat = new Combat(player);
	this->stat_System = new Stat_System();

	int RanNum1 = rand() % 6 + 1;
	int RanNum2 = rand() % 10 + 1;


	items *newItem = new items();
	newItem->GenItem(RanNum1, RanNum2);
	std::cout << newItem->ItemName << std::endl;

	player->Equipitem(newItem);
	

	mouseMutex.lock();
	cx = get_blit3d()->screenWidth / 2;
	cy = get_blit3d()->screenHeight / 2;
	mouseMutex.unlock();
	
	get_blit3d()->SetMode(Blit3DRenderMode::BLIT3D); //change to 2d mode before drawing sprites/text!

	prog = get_blit3d()->sManager->UseShader("shader.vert", "shader.frag"); //load/compile/link

	//lighting variables
	glm::vec3 LightPosition = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 LightIntensity = glm::vec3(0.4f, 1.0f, 0.0f);

	//send lighting info to the shader
	prog->setUniform("LightPosition", LightPosition);
	prog->setUniform("LightIntensity", LightIntensity);

	//send matrices to the shader
	prog->setUniform("projectionMatrix", get_blit3d()->projectionMatrix);
	prog->setUniform("viewMatrix", get_blit3d()->viewMatrix);

	mesh_Cannon = mesh_mgr.Import_S3D_File("APC_Cannon.S3D");
	mesh_Hull = mesh_mgr.Import_S3D_File("APC_Hull.S3D");
	mesh_Turret = mesh_mgr.Import_S3D_File("APC_Turret.S3D");
	mesh_Wheel = mesh_mgr.Import_S3D_File("APC_Wheel.S3D");
	mesh_Box = mesh_mgr.Import_S3D_File("box.S3D");
	mesh_Golem = mesh_mgr.Import_S3D_File("golem.S3D");

	get_blit3d()->projectionMatrix *= glm::perspective(45.0f, (GLfloat)(get_blit3d()->screenWidth) / (GLfloat)(get_blit3d()->screenHeight), 0.1f, 10000.0f);
}

inline void game::DeInit(void)
{
	delete stat_System;
	delete newItem;
	
	delete mesh_Cannon;
	delete mesh_Hull;
	delete mesh_Turret;
	delete mesh_Wheel;
	delete mesh_Box;
	delete mesh_Golem;

	delete font;

	dbg::FileLog_Mgr::Stop();
}

inline void game::Update(double& seconds)
{
	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	angle = angle + static_cast<float>(seconds)* 30;
	while (angle > 360)	angle = angle - 360;
	font->ChangeFontSize(angle / 3);

	mesh_Cannon->Update(seconds);
	mesh_Hull->Update(seconds);
	mesh_Turret->Update(seconds);
	mesh_Wheel->Update(seconds);
	mesh_Box->Update(seconds);
	mesh_Golem->Update(seconds);
}

inline void game::Draw(void)
{	
	glClearColor(0.8f, 0.6f, 0.7f, 0.0f);	//clear colour: r,g,b,a 	
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw sprites, from front to back
	get_blit3d()->SetMode(Blit3DRenderMode::BLIT3D);

	font->Write(false, 22, 45, "pooping out my nipples!");

	glm::vec3 LightIntensity = glm::vec3(1.0f, 1.0f, 1.0f);
	prog->setUniform("LightIntensity", LightIntensity);

	mesh_Cannon->Scale(1.0f, 1.0f, 1.0f);
	mesh_Cannon->Transform(-10, 0, -50.0f);
	mesh_Cannon->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Hull->Scale(1.0f, 1.0f, 1.0f);
	mesh_Hull->Transform(-5, 0, -50.0f);
	mesh_Hull->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Turret->Scale(1.0f, 1.0f, 1.0f);
	mesh_Turret->Transform(0, 0, -50.0f);
	mesh_Turret->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Wheel->Scale(1.0f, 1.0f, 1.0f);
	mesh_Wheel->Transform(5, 0, -50.0f);
	mesh_Wheel->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Box->Scale(1.0f, 1.0f, 1.0f);
	mesh_Box->Transform(10, 0, -50.0f);
	mesh_Box->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Golem->Scale(0.1f, 0.1f, 0.1f);
	mesh_Golem->Transform(0, 0, -30.0f);
	mesh_Golem->Rotate((float)angle, 1.0f, 1.0f, 1.0f);

	mesh_Cannon->Draw();
	mesh_Hull->Draw();
	mesh_Turret->Draw();
	mesh_Wheel->Draw();
	mesh_Box->Draw();
	mesh_Golem->Draw();

	glBindVertexArray(0);//turn off vao again

	glClear(GL_DEPTH_BUFFER_BIT);
}

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
inline void game::DoInput(int& key, int& scancode, int& action, int& mods)
{
	if ( action == GLFW_PRESS )
	{
		KeyInput_Mgr.Add(key);
	}
	else if ( action == GLFW_RELEASE )
	{
		KeyInput_Mgr.Remove(key);
	}
}

inline void game::DoCursor(double& x, double& y)
{
	mouseMutex.lock();
	cx = (float)x;
	cy = get_blit3d()->screenHeight - (float)y;
	mouseMutex.unlock();
}