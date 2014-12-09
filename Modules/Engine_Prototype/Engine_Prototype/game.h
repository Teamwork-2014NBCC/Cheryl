#ifndef GAME_H_
#define GAME_H_

#include <blit3d/Blit3D.h>

#include <atomic>
#include <mutex>

#include "texture_mgr.h"
#include "mesh_mgr.h"
#include "Font_Handler.h"

#include "input.h"
#include "Player.h"
#include "Stat_System.h"
#include "Combat.h"



class game
{
private:
	input_mgr KeyInput_Mgr;

	GLSLProgram *prog = NULL;
	Font_Handler *font = nullptr;
	Combat *combat = nullptr;

	items *newItem = nullptr;
	Player *player = nullptr;
	Stat_System *stat_System = nullptr;

	std::mutex mouseMutex;
	float cx, cy;



	std::atomic<float> angle = 0;

	S3DMesh* mesh_Cannon = NULL;
	S3DMesh* mesh_Hull = NULL;
	S3DMesh* mesh_Turret = NULL;
	S3DMesh* mesh_Wheel = NULL;
	S3DMesh* mesh_Box = NULL;
	S3DMesh* mesh_Golem = NULL;

protected:
public:
	Texture_Manager txtr_mgr;
	S3DMesh_Manager mesh_mgr;

	void Init();
	void DeInit();
	void Update(double& seconds);
	void Draw();
	void DoInput(int& key, int& scancode, int& action, int& mods);
	void DoCursor(double& x, double& y);
};

#endif
