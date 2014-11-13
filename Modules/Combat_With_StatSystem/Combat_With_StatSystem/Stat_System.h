#ifndef STAT_SYSTEM_H
#define STAT_SYSTEM_H

#include <string>

class Stat_System
{
protected:
	int level = 0;						//The level of a player/creature
	int str = 0;						//Damage increases with str
	int intel = 0;						//MDamage increases with intel
	int spd = 0;						//Hit, dodge, etc...
	int con = 0;						//Health, Damage reduction
	int damage = 0;						//Amount of damage you do based on str
	int physSkillDamage = 0;			//Damage done with str based skills
	int magicSkillDamage = 0;			//Damage done with int based skills
	int damageReduction = 0;			//Amount of damage you take, reduced by con
	int health = 0;						//Hp stat, based on con and level
	int movementSpeed = 0;				//movement speed based on spd
	int dodgeChance = 0;				//dodge chance based on spd
	int attackSpeed = 0;				//att speed based on spd and str
	int hitChance = 0;					//hit chance based on  spd
	int exp = 0;						//Current exp
	int expToLevel = 100;				//Exp to next level
	int statPoints = 0;					//Stat points per level
	int abilityPoints = 0;				//Ability points per however many levels.

	std::string currentEquip;			//currently equipped weapon
	


public:

	
	int calcHealth();				//adjusts hp based on con
	int calcDamage();				//adjusts dmg based on str
	int calcAttackSpeed();			//adjusts attack speed based on spd and str
	int calcMoveSpeed();			//adjusts movement based on spd
	int calcDodgeChance();			//adjusts dodge based on spd
	int calcHitChance();			//adjusts the hit chanc based on spd
	int calcDamageReduction();		//adjusts dmg taken based on con
	int calcMagicSkillDamage();		//adjusts magic skill dmg based on intel
	int calcPhysicalSkillDamage();	//adjusts physical skill dmg based on str
};

class base_game_entity : public Stat_System
{};

#endif STAT_SYSTEM_H