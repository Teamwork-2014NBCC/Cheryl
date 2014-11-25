#include"player.h"
#include"Stat_System.h"

int Stat_System::calcHealth()
{
	health = (20 + (con * 2)) * (((float)con / 50) + 1);  //Calculates the health 20 + 2con * (1 + (con/50))
	return(health);
	
}

int Stat_System::calcDamage()
{
	if (str <= 18)
	{
		damage = (0 + (str * 1)) *(((float)str / 100) + 1); //calculates damage 0 + str * (1 + (str/100))
	}
	else if (str > 18)
	{
		damage = 20 + (1 + ((str-18) * 1)) *(((float)str / 70) + 1);//calculates damage 20 + str -18 * (1 + (str/70))
	}
	return(damage);
	
}

int Stat_System::calcDamageReduction()
{
	damageReduction = (0 + con / 2.5);  // calculated dmg reduction  0 + con/2.5

	return(damageReduction);
}

int Stat_System::calcMagicSkillDamage()
{
	if (intel <= 16)
	{
		magicSkillDamage = (3 + (intel * 1)) * (((float)intel / 30) + 1); //calculates magic skill damage 0 + intel * (1 + (intel/50))
	}
	else if (intel > 16)
	{
		magicSkillDamage = (15 + ((intel - 16) * 1)) * (((float)intel / 15) + 1);//calculates magic skill damage 16 + intel-16 * (1 + (intel/25))
	}
	return(magicSkillDamage);
}

int Stat_System::calcPhysicalSkillDamage()
{
	if (str <= 12)
	{
		physSkillDamage = (1 + (str * 1)) *(((float)str / 60) + 1); //calculates skill damage 1 + str * (1 + (str/60))
	}
	else if (str > 12)
	{
		physSkillDamage = 19 + (1 + ((str - 12) * 1)) *(((float)str / 50) + 1);  //calculates skill damage 1 + (str-12) * (1 + (str/50))
	}
	return(physSkillDamage);
}

int Stat_System::calcAttackSpeed()
{
	attackSpeed = 10 * (((float)spd * 5 / 100) + 1); //calculates att speed  10 * ((spd *5 /100)+ 1)

	return(attackSpeed);
}

int Stat_System::calcMoveSpeed()
{
	movementSpeed = 100 * (((float)spd / 100) + 1); // calculates att speed 100 * ((spd /100)+ 1)

	return(movementSpeed);
}

int Stat_System::calcHitChance()
{
	hitChance = 75 * (((float)spd / 30) + 1); // calculate hit chance 75 * ((spd/30)+ 1)

	return(hitChance);
}

int Stat_System::calcDodgeChance()
{
	dodgeChance = spd * 2; // calculate dodge chance spd * 2

	return(dodgeChance);
}