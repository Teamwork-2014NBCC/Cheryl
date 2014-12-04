#ifndef ENEMY_H_
#define ENEMY_H_

#include "Stat_System.h"

class Enemy: public base_game_entity
{

public:

	Enemy(int Str, int Intel, int Spd, int Con);

	void PrintStats(Enemy *e);


};


#endif
