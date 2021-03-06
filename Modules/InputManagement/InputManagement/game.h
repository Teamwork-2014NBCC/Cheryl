#ifndef GAME_H_
#define GAME_H_

#include <blit3d/Blit3D.h>

#include <atomic>
#include <mutex>

#include "input.h"


class game
{
private:
	BFont *bfont = nullptr;
	input_mgr Input_Mgr;
	std::mutex mouseMutex;
	float cx, cy;
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
