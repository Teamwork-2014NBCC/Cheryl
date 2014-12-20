#ifndef _ITEMS_H_                                     
#define _ITEMS_H_

#include <chrono>
#include <time.h>
#include <algorithm>
#include <vector> 
#include <stdlib.h>

class items
{
public:

	int RanNum1 = rand() % 6 + 1;
	int RanNum2 = rand() % 10 + 1;
	std::string ItemName;
	int strMod = 0;						    //Damage increases with str
	int intelMod = 0;						//MDamage increases with intel
	int spdMod = 0;						    //Hit, dodge, etc...
	int conMod = 0;						    //Health, Damage reduction
	int damageMod = 0;						//Amount of damage you do based on str
	int physSkillDamageMod = 0;			    //Damage done with str based skills
	int magicSkillDamageMod = 0;			//Damage done with int based skills
	int damageReductionMod = 0;				//Amount of damage you take, reduced by con
	int healthMod = 0;						//Hp stat, based on con and level
	int movementSpeedMod = 0;				//movement speed based on spd
	int dodgeChanceMod = 0;				    //dodge chance based on spd
	int attackSpeedMod = 0;				    //att speed based on spd and str
	int hitChanceMod = 0;					//hit chance based on  spd

	//temporary values for stat modifiers
	int tempStrMod = 0;
	int tempIntelMod = 0;
	int tempSpdMod = 0;
	int tempConMod = 0;
	int tempDamageMod = 0;
	int tempMagicSkillDamageMod = 0;
	int tempPhysicalSkillDamageMod = 0;
	int tempDamageReductionMod = 0;




	void GenRanNum();
	void GenItem(int RanNum1,int RanNum2);



};


class RanNumGen
{
public:

	int RanNum;
	int GenRanNum(int MinRange, int MaxRange);

};


#endif 