#include "combat.h"


Combat::Combat(Player *player)
{
	this->player = player;
}
void Combat::Basic_Attack()
{
	if (Target ==  true)
	{
		doCombat();
	}
	
}

void Combat::Special_Attack()
{

	//requires abilities

}


void Combat::doCombat()
{
	if (!InRange())
	{
		damagedealt = 0;
	}
	else
	{
		if(!Evade());
		{
			
		}

	}
	damagedealt = 0;
}

void Combat::SetTarget(base_game_entity* target)
{
	this->target = target;
}


bool Combat::InRange()
{

	int deltaX = target->getX() - player->getX();
	deltaX = deltaX < 0 ? deltaX * -1 : deltaX;

	int deltaY = target->getY() - player->getY();
	deltaY = deltaY < 0 ? deltaY * -1 : deltaY;

	//check four states of if
	if ((deltaX == 1) ^ (deltaY == 1))
	{
		return true;
	}
	
	return false;
}

bool Combat::Evade()
{

	if (player->getHitChance()/* > enemy->dodgechance()*/)
	{
		return false;
	}
	else
		return true;


}
