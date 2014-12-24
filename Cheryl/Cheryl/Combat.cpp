#include "player.h"
#include "combat.h"


Combat::Combat(Player *player)
{

}
void Combat::B_Attack()
{

 	//player.GetBaseDamage(damagedealt);
	doCombat(damagedealt);

}

void Combat::S_Attack()
{

	//requires abilities

}


void Combat::doCombat(int damagedealt)
{
	if (!InRange())
	{
		damagedealt = 0;

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

