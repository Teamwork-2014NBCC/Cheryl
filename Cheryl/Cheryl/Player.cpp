#include "Player.h"

//This creates our base player (no adjustments made)
Player::Player(int statpoints)
{
	/*this->statPoints = statpoints;
	this->currentEquip = "Mace";
	this->strength = 3;
	this->intelligence = 3;
	this->speed = 3;
	this->constitution = 3;
	this->exp = 0;
	this->expToLevel = 100;
	this->damage = get_Damage();
	this->physSkillDamage = get_PhysicalSkillDamage();
	this->attackSpeed = get_AttackSpeed();
	this->magicSkillDamage = get_MagicSkillDamage();
	this->dodgeChance = calc_DodgeChance();
	this->hitChance = get_HitChance();
	this->movementSpeed = get_MoveSpeed();
	this->health = get_Health();
	this->damageReduction = get_DamageReduction();

	LevelUp();*/
}
//each level a player gains 5 stat points to add
//to their character which will adjusts it's damage,health,speed, etc...
void Player::LevelUp()
{
	//bool exit = false;
	//level += 1;
	//statPoints += 5;
	//std::cout << "Your level is currently " << level << ". You have " << statPoints << " stat points" << std::endl;


	//std::cout << "\nWeapon: " << currentEquip << std::endl;
	//std::cout << "\n1.str = " << strength << std::endl;
	//std::cout << "2.intel = " << intelligence << std::endl;
	//std::cout << "3.spd = " << speed << std::endl;
	//std::cout << "4.con = " << constitution << std::endl;
	//std::cout << "\nHealt: " << health << std::endl;
	//std::cout << "Damage: " << damage << std::endl;
	//std::cout << "Damage Reduction: " << damageReduction << std::endl;
	//std::cout << "Magic Damage: " << magicSkillDamage << std::endl;
	//std::cout << "Skill Damage: " << physSkillDamage << std::endl;
	//std::cout << "Hit Chance: " << hitChance << std::endl;
	//std::cout << "Dodge Chance: " << dodgeChance << std::endl;
	//std::cout << "Attack Speed: " << attackSpeed << std::endl;
	//std::cout << "Movement Speed: " << movementSpeed << std::endl;


	//while (this->statPoints != 0 && exit == false)	//while there are stat points left or the player has not exited
	//{

	//	char tempStatAdjust = ' ';


	//	while (!_kbhit()){}
	//	tempStatAdjust = _getch();			//get key input from player

	//	switch (tempStatAdjust)						//adjusts stats based on input from player
	//	{
	//	case '1':
	//		strength += 1;
	//		statPoints -= 1;
	//		damage = get_Damage();
	//		physSkillDamage = get_PhysicalSkillDamage();
	//		attackSpeed = get_AttackSpeed();
	//		break;
	//	case '2':
	//		intelligence += 1;
	//		statPoints -= 1;
	//		magicSkillDamage = get_MagicSkillDamage();
	//		break;
	//	case '3':
	//		speed += 1;
	//		statPoints -= 1;
	//		dodgeChance = calc_DodgeChance();
	//		hitChance = get_HitChance();
	//		movementSpeed = get_MoveSpeed();
	//		attackSpeed = get_AttackSpeed();
	//		break;
	//	case '4':
	//		constitution += 1;
	//		statPoints -= 1;
	//		health = get_Health();
	//		damageReduction = get_DamageReduction();
	//		break;
	//	default:
	//		std::cout << "sukadikbro you did it wrong" << std::endl;
	//	}
	//	//displays all the information
	//	system("cls");
	//	std::cout << "Your level is currently " << level << ". You have " << statPoints << " stat points" << std::endl;
	//	std::cout << "\nWeapon: " << currentEquip << std::endl;
	//	std::cout << "\n1.str = " << strength << std::endl;
	//	std::cout << "2.intel = " << intelligence << std::endl;
	//	std::cout << "3.spd = " << speed << std::endl;
	//	std::cout << "4.con = " << constitution << std::endl;
	//	std::cout << "\nHealt: " << health << std::endl;
	//	std::cout << "Damage: " << damage << std::endl;
	//	std::cout << "Damage Reduction: " << damageReduction << std::endl;
	//	std::cout << "Magic Damage: " << magicSkillDamage << std::endl;
	//	std::cout << "Skill Damage: " << physSkillDamage << std::endl;
	//	std::cout << "Hit Chance: " << hitChance << std::endl;
	//	std::cout << "Dodge Chance: " << dodgeChance << std::endl;
	//	std::cout << "Attack Speed: " << attackSpeed << std::endl;
	//	std::cout << "Movement Speed: " << movementSpeed << std::endl;

	//}
}

int Player::GetBaseDamage(int damagedealt)
{

	//damagedealt = damage;
	return damagedealt;
}

void Player::AdjustPlayerHealth(int damagedealt)
{
	health = health - damagedealt;

	std::cout << health << std::endl;

}

Player::~Player()
{
}