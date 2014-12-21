#include <blit3d\Blit3D.h>

#include <atomic>
#include <stdio.h>
#include <conio.h>
#include <thread>

#include "game.h"
#include "global.h"
#include "log.h"

#ifdef _WIN32
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#endif

//GLOBAL DATA

Blit3D* get_blit3d()
{
	static Blit3D* the_blit3D = new Blit3D( Blit3DWindowModel::DECORATEDWINDOW, 1000, 600 );
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
void Update( double seconds )
{
	get_game_engine().Update( seconds );
}
void Draw()
{
	get_game_engine().Draw();
}
void DoInput( int key, int scancode, int action, int mods )
{
	get_game_engine().DoInput( key, scancode, action, mods );
}
void DoCursor( double x, double y )
{
	get_game_engine().DoCursor( x, y );
}

inline void game::Init()
{
	dbg::FileLog_Mgr::RegisterNewLog( L"Memory Issues.log" );
	dbg::FileLog_Mgr::Start();

	//This is the directory Meshes and Textures are found in
	File_Manager::Register_Directory( textures );
	File_Manager::Register_Directory( models );

	// DARREN'S PROJECT DIRECTORY (right click a .cpp or .h tab above and open containing folder, copy paste directory into string)
	File_Manager::Register_Directory( "" );

	//load sprites
	txtr_mgr.LoadAll();
	mesh_mgr.Load_All();
	Keeper_of_the_Font = new Font_Handler();

	The_Maze.Descend();

	TransformerNode* myBox = new TransformerNode( &SceneGraph );
	glm::vec3 axis;
	axis.z = -1;
	myBox->Transform( 30, axis );
	myBox->Set_Mesh( mesh_mgr.Get_Mesh( "box.s3d" ) );/**/

	Init_GFX();
}

void game::Init_GFX()
{
	//enable blending
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	//We should setup our lighting shader
	GLSLProgram* prog = get_blit3d()->sManager->UseShader( "lighting.vert", "lighting.frag" );
	//Setting shader variable values
	get_blit3d()->projectionMatrix *= glm::perspective( 45.0f, (GLfloat)( get_blit3d()->screenWidth ) / (GLfloat)( get_blit3d()->screenHeight ), 0.1f, 10000.0f );
	glm::vec3 LightPosition = glm::vec3( 1.0f, 1.0f, 1.0f );
	glm::vec3 LightIntensity = glm::vec3( 1.0f, 1.0f, 1.0f );
	//Binding variables to shader
	prog->setUniform( "projectionMatrix", get_blit3d()->projectionMatrix );
	prog->setUniform( "viewMatrix", get_blit3d()->viewMatrix );
	prog->setUniform( "LightPosition", LightPosition );
	prog->setUniform( "LightIntensity", LightIntensity );/**/
}

inline void game::DeInit( void )
{
	delete Keeper_of_the_Font;
}

inline void game::Update( double& seconds )
{
	SceneGraph.Update( seconds );
}

inline void game::Draw( void )
{
	glClearColor( 0.8f, 0.6f, 0.7f, 0.0f );	//clear colour: r,g,b,a
	// wipe the drawing surface clear
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	get_blit3d()->SetMode( Blit3DRenderMode::BLIT3D );
	//draw sprites, from front to back
	SceneGraph.Draw();

	//get_blit3d()->SetMode( Blit3DRenderMode::BLIT2D, get_blit3d()->shader2d );
	//Keeper_of_the_Font->Write( false, 100, 100, "Cheryl: Hello World!" );

	//glfwSwapBuffers( get_blit3d()->window );
}

//the key codes/actions/mods for DoInput are from GLFW: check its documentation for their values
inline void game::DoInput( int& key, int& scancode, int& action, int& mods )
{
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
	{
		get_blit3d()->Quit(); //start the shutdown sequence
	}
	if ( action == GLFW_PRESS )
	{
		KeyInput_Mgr.Add( key );
	}
	else if ( action == GLFW_RELEASE )
	{
		KeyInput_Mgr.Remove( key );
	}
}

inline void game::DoCursor( double& x, double& y )
{
	mouseMutex.lock();
	cx = (float)x;
	cy = get_blit3d()->screenHeight - (float)y;
	mouseMutex.unlock();
}