#include <blit3d\Blit3D.h>
#include <debug_toolset.h>

#include <atomic>
#include <stdio.h>
#include <conio.h>
#include <thread>

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
	static Blit3D* the_blit3D = new Blit3D(Blit3DWindowModel::DECORATEDWINDOW, 700, 400);
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
	bfont = nullptr;
	//assert(bfont != NULL); //make sure it loaded

	mouseMutex.lock();
	cx = get_blit3d()->screenWidth / 2;
	cy = get_blit3d()->screenHeight / 2;
	mouseMutex.unlock();
	
	get_blit3d()->SetMode(Blit3DRenderMode::BLIT3D); //change to 2d mode before drawing sprites/text!
}

inline void game::DeInit(void)
{

	dbg::FileLog_Mgr::Stop();
}

inline void game::Update(double& seconds)
{
	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
}

inline void game::Draw(void)
{	
	glClearColor(0.8f, 0.6f, 0.7f, 0.0f);	//clear colour: r,g,b,a 	
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw sprites, from front to back

	glClear(GL_DEPTH_BUFFER_BIT);
	//usually want to draw text last
	//std::string text = "Blit3D 2D sprite example.";
	//float textWidth = bfont->WidthText(false, text.c_str());
	//bfont->DrawText(false, get_blit3d()->screenWidth - 20 - textWidth, 50, text.c_str());
}

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
inline void game::DoInput(int& key, int& scancode, int& action, int& mods)
{
	if ( action == GLFW_PRESS )
	{
		Input_Mgr.Add(key);
	}
	else if ( action == GLFW_RELEASE )
	{
		Input_Mgr.Remove(key);
	}
}

inline void game::DoCursor(double& x, double& y)
{
	mouseMutex.lock();
	cx = (float)x;
	cy = get_blit3d()->screenHeight - (float)y;
	mouseMutex.unlock();
}