#include "Enemy.h"
#include "Enemy_Mgr.h"
#include "player.h"

Enemy::Enemy(int Str, int Intel, int Spd, int Con)
{

	this->str = Str;
	this->intel = Intel;
	this->spd = Spd;
	this->con = Con;
	this->damage = calcDamage();
	this->physSkillDamage = calcPhysicalSkillDamage();
	this->attackSpeed = calcAttackSpeed();
	this->magicSkillDamage = calcMagicSkillDamage();
	this->dodgeChance = calcDodgeChance();
	this->hitChance = calcHitChance();
	this->movementSpeed = calcMoveSpeed();
	this->health = calcHealth();
	this->damageReduction = calcDamageReduction();

	PrintStats(this);

}


void Enemy::PrintStats(Enemy *e)
{
	std::cout << "\n1.str = " << str << std::endl;
	std::cout << "2.intel = " << intel << std::endl;
	std::cout << "3.spd = " << spd << std::endl;
	std::cout << "4.con = " << con << std::endl;
	std::cout << "\nHealth: " << health << std::endl;
	std::cout << "Damage: " << damage << std::endl;
	std::cout << "Damage Reduction: " << damageReduction << std::endl;
	std::cout << "Magic Damage: " << magicSkillDamage << std::endl;
	std::cout << "Skill Damage: " << physSkillDamage << std::endl;
	std::cout << "Hit Chance: " << hitChance << std::endl;
	std::cout << "Dodge Chance: " << dodgeChance << std::endl;
	std::cout << "Attack Speed: " << attackSpeed << std::endl;
	std::cout << "Movement Speed: " << movementSpeed << std::endl;

}

