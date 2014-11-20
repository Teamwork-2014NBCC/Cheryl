#include "Player.h"


//This creates our base player (no adjustments made)
Player::Player(int statpoints)
{
	this->statPoints = statpoints;
	this->currentEquip = "Mace";
	this->str = 3;
	this->intel = 3;
	this->spd = 3;
	this->con = 3;
	this->exp = 0;
	this->expToLevel = 100;
	this->damage = calcDamage();
	this->physSkillDamage = calcPhysicalSkillDamage();
	this->attackSpeed = calcAttackSpeed();
	this->magicSkillDamage = calcMagicSkillDamage();
	this->dodgeChance = calcDodgeChance();
	this->hitChance = calcHitChance();
	this->movementSpeed = calcMoveSpeed();
	this->health = calcHealth();
	this->damageReduction = calcDamageReduction();

	//LevelUp();
}
//each level a player gains 5 stat points to add
//to their character which will adjusts it's damage,health,speed, etc...
void Player::LevelUp()
{
	bool exit = false;
	level += 1;
	statPoints += 5;
	std::cout << "Your level is currently " << level << ". You have " << statPoints << " stat points" << std::endl;


	std::cout << "\nWeapon: " << currentEquip << std::endl;
	std::cout << "\n1.str = " << str << std::endl;
	std::cout << "2.intel = " << intel << std::endl;
	std::cout << "3.spd = " << spd << std::endl;
	std::cout << "4.con = " << con << std::endl;
	std::cout << "\nHealt: " << health << std::endl;
	std::cout << "Damage: " << damage << std::endl;
	std::cout << "Damage Reduction: " << damageReduction << std::endl;
	std::cout << "Magic Damage: " << magicSkillDamage << std::endl;
	std::cout << "Skill Damage: " << physSkillDamage << std::endl;
	std::cout << "Hit Chance: " << hitChance << std::endl;
	std::cout << "Dodge Chance: " << dodgeChance << std::endl;
	std::cout << "Attack Speed: " << attackSpeed << std::endl;
	std::cout << "Movement Speed: " << movementSpeed << std::endl;



	while (this->statPoints != 0 && exit == false)	//while there are stat points left or the player has not exited
	{

		char tempStatAdjust = ' ';



		while (!_kbhit()){}
		tempStatAdjust = _getch();			//get key input from player

		switch (tempStatAdjust)						//adjusts stats based on input from player
		{
		case '2':
			str += 1;
			statPoints -= 1;
			damage = calcDamage();
			physSkillDamage = calcPhysicalSkillDamage();
			attackSpeed = calcAttackSpeed();
			break;
		case '3':
			intel += 1;
			statPoints -= 1;
			magicSkillDamage = calcMagicSkillDamage();
			break;
		case '4':
			spd += 1;
			statPoints -= 1;
			dodgeChance = calcDodgeChance();
			hitChance = calcHitChance();
			movementSpeed = calcMoveSpeed();
			attackSpeed = calcAttackSpeed();
			break;
		case '5':
			con += 1;
			statPoints -= 1;
			health = calcHealth();
			damageReduction = calcDamageReduction();
			break;
		default:
			std::cout << "sukadikbro you did it wrong" << std::endl;
		}
		//displays all the information
		system("cls");
		std::cout << "Your level is currently " << level << ". You have " << statPoints << " stat points" << std::endl;
		std::cout << "\nWeapon: " << currentEquip << std::endl;
		std::cout << "\n1.str = " << str << std::endl;
		std::cout << "2.intel = " << intel << std::endl;
		std::cout << "3.spd = " << spd << std::endl;
		std::cout << "4.con = " << con << std::endl;
		std::cout << "\nHealt: " << health << std::endl;
		std::cout << "Damage: " << damage << std::endl;
		std::cout << "Damage Reduction: " << damageReduction << std::endl;
		std::cout << "Magic Damage: " << magicSkillDamage << std::endl;
		std::cout << "Skill Damage: " << physSkillDamage << std::endl;
		std::cout << "Hit Chance: " << hitChance << std::endl;
		std::cout << "Dodge Chance: " << dodgeChance << std::endl;
		std::cout << "Attack Speed: " << attackSpeed << std::endl;
		std::cout << "Movement Speed: " << movementSpeed << std::endl;

	}
}
//adjusts stats based on generated item that is equiped.
void Player::Equipitem(items* newItem)	
{
	
	str += newItem->strMod;
	intel += newItem->intelMod;
	spd += newItem->spdMod;
	con += newItem->conMod;
	damage += newItem->damageMod;
	magicSkillDamage += newItem->magicSkillDamageMod;
	physSkillDamage += newItem->physSkillDamageMod;
	damageReduction += newItem->damageReductionMod;


	str -= tempStrMod;
	intel -= tempIntelMod;
	spd -= tempSpdMod;
	con -= tempConMod;
	damage -= tempDamageMod;
	magicSkillDamage -= tempMagicSkillDamageMod;
	physSkillDamage -= tempPhysicalSkillDamageMod;
	damageReduction -= tempDamageReductionMod;

	
	tempStrMod = newItem->strMod;
	tempIntelMod = newItem->intelMod;
	tempSpdMod = newItem->spdMod;
	tempConMod = newItem->conMod;
	tempDamageMod = newItem->damageMod;
	tempMagicSkillDamageMod = newItem->magicSkillDamageMod;
	tempPhysicalSkillDamageMod = newItem->physSkillDamageMod;
	tempDamageReductionMod = newItem->damageReductionMod;

	currentEquip = newItem->ItemName;

	damage = calcDamage();
	physSkillDamage = calcPhysicalSkillDamage();
	attackSpeed = calcAttackSpeed();
	magicSkillDamage = calcMagicSkillDamage();
	dodgeChance = calcDodgeChance();
	hitChance = calcHitChance();
	movementSpeed = calcMoveSpeed();
	health = calcHealth();
	damageReduction = calcDamageReduction();


	system("cls");
	std::cout << "\nWeapon: " << currentEquip << std::endl;
	std::cout << "\n1.str = " << str << std::endl;
	std::cout << "2.intel = " << intel << std::endl;
	std::cout << "3.spd = " << spd << std::endl;
	std::cout << "4.con = " << con << std::endl;
	std::cout << "\nHealt: " << health << std::endl;
	std::cout << "Damage: " << damage << std::endl;
	std::cout << "Damage Reduction: " << damageReduction << std::endl;
	std::cout << "Magic Damage: " << magicSkillDamage << std::endl;
	std::cout << "Skill Damage: " << physSkillDamage << std::endl;
	std::cout << "Hit Chance: " << hitChance << std::endl;
	std::cout << "Dodge Chance: " << dodgeChance << std::endl;
	std::cout << "Attack Speed: " << attackSpeed << std::endl;
	std::cout << "Movement Speed: " << movementSpeed << std::endl;
	

}

//int Player::GetBaseDamage(int damagedealt)
//{
//
//	damagedealt = damage;
//	return damagedealt;
//}
//
//void Player::AdjustPlayerHealth(int damagedealt)
//{
//	health = health - damagedealt;
//
//	std::cout << health << std::endl;
//
//}