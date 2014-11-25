#ifndef GAME_H_
#define GAME_H_

#include <blit3d/Blit3D.h>

#include <atomic>
#include <mutex>

#include "input.h"
#include "Player.h"
#include "Stat_System.h"
#include "Combat.h"
#include "S3DMesh.h"
#include "Font_Handler.h"


class game
{
private:
	Font_Handler *font = nullptr;
	Combat *combat = nullptr;
	items *newItem = nullptr;
	Player *player = nullptr;
	Stat_System *stat_System = nullptr;
	input_mgr Input_Mgr;
	std::mutex mouseMutex;
	float cx, cy;


	GLSLProgram *prog = NULL;

	std::atomic<float> angle = 0;

	S3DMesh* mesh_Cannon = NULL;
	S3DMesh* mesh_Hull = NULL;
	S3DMesh* mesh_Turret = NULL;
	S3DMesh* mesh_Wheel = NULL;
	S3DMesh* mesh_Box = NULL;
	S3DMesh* mesh_Golem = NULL;

protected:
public:
	void Init();
	void DeInit();
	void Update(double& seconds);
	void Draw();
	void DoInput(int& key, int& scancode, int& action, int& mods);
	void DoCursor(double& x, double& y);
};

#endif
