#pragma once
#ifndef SHIP_H
#define SHIP_H

#define _USE_MATH_DEFINES

#include "GameObject.h"
#include <stdlib.h>
#include <string>
#include "ShipWeapon.h"
#include <vector>
#include "GameLogicSmallStructs.h"
#include <cmath>
#include <iostream>
#include "AttackAnim.h"

using namespace std;

class Ship : public GameObject
{
	// Vars
	int facing = 0;
	string name; // What the player sees as the name of the ship, may be able to be changed by player.
	Coordinate Location;
	int maxHullHP;
	int currentHullHP;
	int maxShieldHP;
	int currentShieldHP;
	int movement; // Number of tiles the ship can move.
	int accuracy;
	int evasion;
	bool fired;
	Ship* targetShip;
	AttackAnim* missile;
	//vector<ShipWeapon> weapons; 
	// int SightRange; // If we get to implementing the fog of war.

public:
	ShipWeapon testWeapon;

	void setFacingLeft();
	void AttackTarget(Ship* TargetShip, ShipWeapon* FiringWeapon);
	int TakeDamage(Ship* AttackingShip, ShipWeapon* FiringWeapon);
	int getRange(Ship* TargetShip);
	int getRange(int, int);
	int getAngle(Ship* TargetShip);
	void setLocation(int, int);
	const char* getName();
	std::string getStringName();
	void Render();
	void Update();

	int getHull();
	
	Ship(string id, string name, int MaxHull, int MaxShield, int Move, int Acc, int Evasion, ShipWeapon weapon, const char* textureSheet, int x, int y);
};

#endif // !SHIP_H
