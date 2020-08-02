#pragma once
#ifndef SHIPWEAPON_H
#define SHIPWEAPON_H

#include "ShipSystem.h"
#include "GameLogicEnums.h"
#include "GameLogicSmallStructs.h"
#include <iostream>


class ShipWeapon : public ShipSystem
{
	int minDamage;
	int maxDamage;
	FiringArc arc;
	int range;
	DamageType type;

public:
	int rollDamage()
	{
		int damageRange = maxDamage - minDamage;
		return ((rand() % damageRange) + minDamage);
	}
	DamageType getType() { return type; }
	bool checkArcRange(int, int);
	ShipWeapon(int = 0, int = 1, FiringArc = FiringArc(0,0), int = 1, DamageType = (1.0f,1.0f));
};

#endif // !SHIPWEAPON_H