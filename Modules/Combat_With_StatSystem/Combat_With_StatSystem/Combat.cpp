#include "combat.h"


Combat::Combat(Player&)
{

}
void Combat::B_Attack()
{

	//movement sets target SetTarget()
	GetDamage(damagedealt);


}

void Combat::S_Attack()
{

	//requires abilities

}


void Combat::doCombat()
{
	if (!InRange())
	{
		//damagedealt = 0;

	}
	else
	{
		if(!Evade());
		{
			//player.AdjustPlayerHealth(damagedealt);
		}

	}
	damagedealt = 0;
}

void Combat::SetTarget(base_game_entity* target)
{

}


bool Combat::InRange()
{
	return true;
}

bool Combat::Evade()
{
	return false;
}

int Combat::GetDamage(int)
{
	//damagedealt = player->damage
	return 1;
}

