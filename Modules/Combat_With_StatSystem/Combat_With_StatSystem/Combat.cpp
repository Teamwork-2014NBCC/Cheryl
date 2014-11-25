#include "combat.h"


Combat::Combat(Player *player)
{

}
void Combat::Basic_Attack()
{

	//calls SetTarget()


}

void Combat::Special_Attack()
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

