#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <conio.h>
#include <string>
#include "items.h"

#include "Stat_System.h"

class Player: protected base_game_entity, items
{	
private:
	items* player_item = nullptr;
public:
							
	Player(int statpoints = 15);							//Constructor for player which will set initial stats
	void LevelUp();											//Adjusts stats based on player preference
	void Equipitem(items* newItem);							//Adjusts stats based on equipped item
	
	int GetBaseDamage(int damagedealt);
	void AdjustPlayerHealth(int damagedealt);
};


#endif PLAYER_H
