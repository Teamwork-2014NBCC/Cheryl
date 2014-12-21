#ifndef STAT_SYSTEM_H
#define STAT_SYSTEM_H

#include <string>

class item;

typedef std::pair<int, int> coords;

struct stat_system
{
	int strength = 0;				//Damage increases with str
	int intelligence = 0;			//MDamage increases with intel
	int speed = 0;					//Hit, dodge, etc...
	int constitution = 0;		//Health, Damage reduction
	int defense = 0;
	int health = 0;					//Hp stat, based on con and level
};

class leveling_system
{
	int level = 1;					//The level of a player/creature
	int exp = 0;						//Current exp
	int expToLevel = 100;		//Exp to next level
	int statPoints = 3;			//Stat points per level
	int abilityPoints = 2;		//Ability points per however many levels.
};

class base_game_entity : protected stat_system, protected leveling_system
{
private:
	int movementSpeed = 0;			//movement speed based on spd
	float dodgeChance = 0;			//dodge chance based on spd
	int damageReduction = 0;		//Amount of damage you take, reduced by con

	int attackSpeed = 0;				//att speed based on spd and str
	float hitChance = 0;				//hit chance based on  spd
	int physSkillDamage = 0;		//Damage done with str based skills
	int magicSkillDamage = 0;		//Damage done with int based skills
	int damage = 0;						//Amount of damage you do based on str

	item* weapon = nullptr;
	item* armour = nullptr;

	coords position;

public:
	base_game_entity()
	{
	}
	void change_weapon( item* new_weapon );
	void change_armour( item* new_armour );

	int get_MoveSpeed();					//adjusts movement based on spd
	float calc_DodgeChance( int Speed_of_Attack );			//adjusts dodge based on spd
	int get_DamageReduction();		//adjusts dmg taken based on con
	int get_Health();							//adjusts hp based on con

	int get_AttackSpeed();					//adjusts attack speed based on spd and str
	int get_HitChance();						//adjusts the hit chanc based on spd
	int get_MagicSkillDamage();		//adjusts magic skill dmg based on intel
	int get_PhysicalSkillDamage();	//adjusts physical skill dmg based on str
	int get_Damage();						//adjusts dmg based on str
};

#endif STAT_SYSTEM_H