#include "Player.h"



void items::GenItem(int RanNum1,int RanNum2)
{
	std::string ItemPrefix = "";
	std::string ItemSuffix = "";

					
	switch (RanNum1)								//generates item prefix based on random chance
	{
	case 1:
		ItemPrefix = "Hammer";
		strMod = strMod + 4;
		spdMod = spdMod - 2;
		break;
	case 2:
		ItemPrefix = "Mace";
		strMod = strMod + 2;
		intelMod = intelMod + 2;
		break;
	case 3:
		ItemPrefix = "Sword";
		strMod = strMod + 2;
		break;
	case 4:
		ItemPrefix = "Bow";
		strMod = strMod + 2;
		spdMod = spdMod + 2;
		break;
	case 5:
		ItemPrefix = "Staff";
		intelMod = intelMod + 4;
		spdMod = spdMod - 1;
		break;
	case 6:
		ItemPrefix = "Flail";
		break;

	default:
		break;
	}



	switch (RanNum2)									//generates item suffix based on random chance
	{
	case 1:
		ItemSuffix = " Of Darkness";
		magicSkillDamageMod = magicSkillDamageMod + 3;
		break;
	case 2:
		ItemSuffix = " Of Light";
		magicSkillDamageMod = magicSkillDamageMod + 3;
		break;
	case 3:
		ItemSuffix = " Of Fire";
		attackSpeedMod = attackSpeedMod + 3;
		break;
	case 4:
		ItemSuffix = " Of Ice";
		damageReductionMod = damageReductionMod + 3;
		break;
	case 5:
		ItemSuffix = " Of Cruelty";
		physSkillDamageMod = physSkillDamageMod + 5;
		healthMod = healthMod - 20;
		break;
	case 6:
		ItemSuffix = " Of Malice";
		magicSkillDamageMod = physSkillDamageMod + 5;
		healthMod = healthMod - 20;
		break;
	case 7:
		ItemSuffix = " Of Vigor";
		healthMod = healthMod + 40;
		break;
	case 8: 
		ItemSuffix = " Of The Whale";
		healthMod = healthMod + 50;
		break;
	case 9:
		ItemSuffix = " Of Kings"; 
		strMod = strMod + 1;
		intelMod = intelMod + 1;
		spdMod = spdMod + 1;
		conMod = conMod + 1;
		break;
	case 10:
		ItemSuffix = " Of Legends";
		strMod = strMod + 2;
		intelMod = intelMod + 2;
		spdMod = spdMod + 2;
		conMod = conMod + 2;
		break;

	default:
		break;
	}
	ItemName = ItemPrefix + ItemSuffix;				//adjusts item name

}

int RanNumGen::GenRanNum(int MinRange, int MaxRange)				//gens random number for item generation
{

	RanNum = rand() % 6 + 1;
	return RanNum;
}