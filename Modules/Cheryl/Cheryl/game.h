#ifndef GAME_H_
#define GAME_H_

#include <blit3d/Blit3D.h>

#include <atomic>
#include <mutex>

#include "input_mgr.h"

#include "texture_mgr.h"
#include "ffont.h"

#include "mesh_mgr.h"
#include "scene_nodes.h"

#include "level_gen.h"

class game
{
private:
	input_mgr KeyInput_Mgr;
	Root_SceneNode SceneGraph;
	Font_Handler* Keeper_of_the_Font = nullptr;
	Dungeon The_Maze = Dungeon( &SceneGraph );

	std::mutex mouseMutex;
	float cx = 10;
	float cy = 10;

protected:
public:
	void Init();
	void Init_GFX();
	void DeInit();
	void Update( double& seconds );
	void Draw();
	void DoInput( int& key, int& scancode, int& action, int& mods );
	void DoCursor( double& x, double& y );
	Texture_Manager txtr_mgr;
	s3d_mesh_mgr mesh_mgr;
};

#endif
