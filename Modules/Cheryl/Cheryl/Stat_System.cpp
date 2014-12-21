#include "Stat_System.h"
#include "Items.h"

int base_game_entity::get_MoveSpeed()
{
	movementSpeed = 100 * (((float)speed / 100) + 1); // calculates att speed 100 * ((spd /100)+ 1)

	return(movementSpeed);
}

float base_game_entity::calc_DodgeChance( int Speed_of_Attack)
{
	dodgeChance = speed * 2; // calculate dodge chance spd * 2

	return(dodgeChance);
}

int base_game_entity::get_DamageReduction()
{
	damageReduction = (0 + constitution / 2.5);  // calculated dmg reduction  0 + con/2.5

	return(damageReduction);
}

int base_game_entity::get_Health()
{
	health = 1;
	auto convert_con_to_hp = [this]( int con )
	{
		health += ( 20 + ( con * 2 ) ) * ( ( (float)con / 50 ) );
	};
	if ( weapon )
	{
		convert_con_to_hp( weapon->get_Con() );
		health += weapon->get_HP();
	}
	if ( armour )
	{
		convert_con_to_hp( armour->get_Con() );
		health += armour->get_HP();
	}
	convert_con_to_hp( constitution );

	return health;
	
}



int base_game_entity::get_AttackSpeed()
{
	attackSpeed = 10 * (((float)speed * 5 / 100) + 1); //calculates att speed  10 * ((spd *5 /100)+ 1)

	return(attackSpeed);
}

int base_game_entity::get_HitChance()
{
	hitChance = 75 * (((float)speed / 30) + 1); // calculate hit chance 75 * ((spd/30)+ 1)

	return(hitChance);
}

int base_game_entity::get_MagicSkillDamage()
{
	if (intelligence <= 16)
	{
		magicSkillDamage = (3 + (intelligence * 1)) * (((float)intelligence / 30) + 1); //calculates magic skill damage 0 + intel * (1 + (intel/50))
	}
	else if (intelligence > 16)
	{
		magicSkillDamage = (15 + ((intelligence - 16) * 1)) * (((float)intelligence / 15) + 1);//calculates magic skill damage 16 + intel-16 * (1 + (intel/25))
	}
	return(magicSkillDamage);
}

int base_game_entity::get_PhysicalSkillDamage()
{
	if (strength <= 12)
	{
		physSkillDamage = (1 + (strength * 1)) *(((float)strength / 60) + 1); //calculates skill damage 1 + str * (1 + (str/60))
	}
	else if (strength > 12)
	{
		physSkillDamage = 19 + (1 + ((strength - 12) * 1)) *(((float)strength / 50) + 1);  //calculates skill damage 1 + (str-12) * (1 + (str/50))
	}
	return(physSkillDamage);
}

int base_game_entity::get_Damage()
{
	if (strength <= 18)
	{
		damage = (0 + (strength * 1)) *(((float)strength / 100) + 1); //calculates damage 0 + str * (1 + (str/100))
	}
	else if (strength > 18)
	{
		damage = 20 + (1 + ((strength-18) * 1)) *(((float)strength / 70) + 1);//calculates damage 20 + str -18 * (1 + (str/70))
	}
	return(damage);
}

