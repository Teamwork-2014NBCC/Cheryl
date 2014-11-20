#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "player.h"


class Combat
{
private:
	Player *player = nullptr;
	
public:
	int damagedealt;
	int damageTaken;
	Combat(Player&);
	//cooldown goes in abilities

	std::string skillused;

	bool inRange;
	bool evade;
	
	void B_Attack();
	void S_Attack();
	void SetTarget(base_game_entity* target);
	bool Evade();
	bool InRange(); 
	std::string GetSkillUsed();
	void doCombat();
	int GetDamage(int);


};
#endif