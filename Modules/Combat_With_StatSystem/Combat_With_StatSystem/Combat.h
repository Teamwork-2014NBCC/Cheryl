#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "player.h"


class Combat
{
private:
	Player *player = nullptr;
	base_game_entity *target = nullptr;

	
public:
	int damagedealt;
	int damageTaken;
	Combat(Player *player);
	//cooldown goes in abilities

	std::string skillused;

	bool inRange;
	bool evade;
	bool Target;
	
	void Basic_Attack();
	void Special_Attack();
	void SetTarget(base_game_entity* target);
	bool Evade();
	bool InRange();
	std::string GetSkillUsed();
	void doCombat();


};
#endif