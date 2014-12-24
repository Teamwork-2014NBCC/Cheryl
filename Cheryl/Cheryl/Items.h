#ifndef _ITEMS_H_                                     
#define _ITEMS_H_

#include "Stat_System.h"

class item : protected stat_system
{
public:
	int get_Str() const
	{
		return strength;
	}
	int get_Intel() const
	{
		return intelligence;
	}
	int get_Speed() const
	{
		return speed;
	}
	int get_Con() const
	{
		return constitution;
	}
	int get_Def() const
	{
		return defense;
	}
	int get_HP() const
	{
		return health;
	}
};

#endif