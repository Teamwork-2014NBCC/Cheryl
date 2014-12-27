#ifndef GAME_H_
#define GAME_H_

#include <blit3d/Blit3D.h>

#include <atomic>
#include <mutex>

#include "input_mgr.h"

#include "texture_mgr.h"
#include "ffont.h"

#include "2d_graphic_mgr.h"
#include "mesh_mgr.h"
#include "scene_nodes.h"

#include "level_gen.h"

class game
{
private:
	input_mgr KeyInput_Mgr;
	Root_SceneNode SceneGraph;
	GLSLProgram* shader_3d = nullptr;
	GLSLProgram* shader_2d = nullptr;
	Font_Handler* Keeper_of_the_Font = nullptr;
	Dungeon The_Maze = Dungeon( &SceneGraph );

	glm::vec3 player_straight_axis;
	glm::vec3 player_side_axis;
	std::mutex mouseMutex;
	float cx = 10;
	float cy = 10;
	int player_x = 1;
	int player_y = 1;

	graphic* G = nullptr;

protected:
	void Init_GFX();
	void Init_Input();
	void Rotate_Camera( float angle );
	void Rotate_Left();
	void Rotate_Right();
	void Move_Forward();
	void Move_Backward();
	void Move_Left();
	void Move_Right();

public:
	void Init();
	void DeInit();
	void Update( double& seconds );
	void Draw();
	void DoInput( int& key, int& scancode, int& action, int& mods );
	void DoCursor( double& x, double& y );

	Texture_Manager txtr_mgr;
	Graphic_Manager graphic_mgr;
	s3d_mesh_mgr mesh_mgr;
};

#endif
