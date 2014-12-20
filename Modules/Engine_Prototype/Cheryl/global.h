#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <blit3d\Blit3D.h>

#include <mutex>

#include "game.h"

extern Blit3D* get_blit3d();
extern game& get_game_engine();

extern string textures;
extern string models;
extern string otherfiles;

extern void Init();
extern void DeInit();
extern void Update(double seconds);
extern void Draw();
extern void DoInput(int key, int scancode, int action, int mods);
extern void DoCursor(double x, double y);

#endif
