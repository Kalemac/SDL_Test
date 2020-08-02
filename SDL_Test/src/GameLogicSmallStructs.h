#pragma once
#ifndef GAMELOGICSMALLSTRUCTS_H
#define GAMELOGICSMALLSTRUCTS_H


struct FiringArc // What directions the given weapon can fire in.
{
	// NOTE: Follows a clockwise pattern. So if you want the front quarter, use 0 and 90.
	// If you want anything NOT in the front quarter, use 90 to 0 (or 360)
	// Assumes that 0 degrees is facing dead ahead.
	int startAngle;
	int endAngle;
	FiringArc(int S = 0, int E = 0) { startAngle = S; endAngle = E; };
};

struct DamageType
{
	float damageShields; // Weapon's damage modifier vs. shields.
	float damageHull; // vs. hull.
	DamageType(float S = 1, float H = 1) { damageShields = S; damageHull = H; };
};

struct Coordinate
{
	int x;
	int y;
};

#endif // !GAMELOGICSMALLSTRUCTS_H
