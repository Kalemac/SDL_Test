#include "Ship.h"
#include "UIFunctions.h"
//#include "text.h"

SDL_Color red = { 255, 20, 20 };
SDL_Color black = {0, 0, 0 };
SDL_Color blue = { 0, 170, 255 };
SDL_Color white = { 255,255,255 };

void Ship::setFacingLeft()
{

	facing = 180;
}

// To-hit roll function. 
void Ship::AttackTarget(Ship* TargetShip, ShipWeapon* FiringWeapon)
{
	int range = getRange(TargetShip);
	std::cout << "Range: " << range;
	int angle = getAngle(TargetShip);
	std::cout << " | Angle: " << angle;
	if(FiringWeapon->checkArcRange(angle, range))
	{ 
		int damage = 0;
		std::cout << " | In Range/Angle: Yes" << endl;
		int toHitRoll = (rand() % 100) + 1;
		toHitRoll += this->accuracy - TargetShip->evasion;
		if (toHitRoll > 50) // If accuracy and evasion are equal, 50% chance of hit.
		{
			damage = TargetShip->TakeDamage(this, FiringWeapon);
		}
		std::cout << "Damage: " << damage << " | Target Shield: " << TargetShip->currentShieldHP << " | Target Hull: " << TargetShip->currentHullHP << endl;

		//SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		//SDL_RenderDrawLine(Game::renderer, getBox().x + 32, getBox().y + 32, TargetShip->getBox().x + 32, TargetShip->getBox().y + 32);
	}
	else
	{
		std::cout << " | In Range/Angle: No" << endl;
	}

	
}

int Ship::TakeDamage(Ship* AttackingShip, ShipWeapon* FiringWeapon)
{
	int totalDamage = 0;
	int damage = FiringWeapon->rollDamage();
	DamageType incomingDamage = FiringWeapon->getType();
	totalDamage = (damage * incomingDamage.damageShields);
	currentShieldHP -= totalDamage;
	if (currentShieldHP < 0)
	{
		// Any damage over shield value bleeds through to hull.
		int remainingDamage = -currentShieldHP;
		totalDamage -= remainingDamage;
		remainingDamage *= (1 / incomingDamage.damageShields); // Removing shield damage multiplier
		remainingDamage *= incomingDamage.damageHull;
		currentHullHP -= remainingDamage;
		totalDamage += remainingDamage; // Add inflicted hull damage to damage total.
		currentShieldHP = 0;
	}
	return totalDamage;
}

int Ship::getRange(Ship* TargetShip) // Range is number of squares of cardinal direction movement to
// get to the target. So up and right is 2, because 1 up, 1 right.
{
	return (abs(this->Location.x - TargetShip->Location.x) + abs(this->Location.y - TargetShip->Location.y));	
}

int Ship::getRange(int x, int y) // Pass the x/y of the grid coordinates
{
	return (abs(this->Location.x - x) + abs(this->Location.y - y));
}

int Ship::getAngle(Ship* TargetShip)
{
	int facingAngle = facing;
	double offsetAngle = 0;
	int offsetX = this->Location.x - TargetShip->Location.x;
	int offsetY = this->Location.y - TargetShip->Location.y;
	offsetY *= -1; // Converts from top-left base for coordinate system to bottom-left.
	if (offsetX == 0)
	{
		if (offsetY < 0) // Above object
		{
			offsetAngle = 90;
		}
		else if (offsetY > 0) // Below object
		{
			offsetAngle = 270;
		}
	}
	else if (offsetX < 0) // To the right of the object, quadrant 1 or 4
	{
		offsetAngle = atan((double)offsetY / (double)offsetX);
		offsetAngle *= 180 / M_PI; // Convert from atan's radians to degrees.
		if (offsetAngle < 0) // If negative, is in quadrant 4.
		{ 
			offsetAngle += 360;
		}
	}
	else if (offsetX > 0) // To the left of the object, quadrant 2 or 3
	{
		offsetAngle = atan((double)offsetY / (double)offsetX);
		offsetAngle *= 180 / M_PI; // Convert from atan's radians to degrees.
		offsetAngle += 180; // Adjust from quadrant 4/1 to quadrant 2/3;
	}
	offsetAngle += facingAngle;
	
	return ((int)offsetAngle % 360);
}

int Ship::getMovePoints()
{
	return movement;
}

int Ship::getLocationX()
{
	return Location.x;
}

int Ship::getLocationY()
{
	return Location.y;
}

void Ship::setLocation(int newX, int newY)
{
	Location.x = newX;
	Location.y = newY;
}

const char* Ship::getName()
{
	return name.c_str();
}

std::string Ship::getStringName() {
	return name;
}


Ship::Ship(string id, string name, int MaxHull, int MaxShield, int Move, int Acc, int Evade, ShipWeapon weapon, const char* textureSheet, int x, int y) : GameObject{ textureSheet, x, y }
{
	this->name = name;
	currentHullHP = maxHullHP = MaxHull;
	currentShieldHP = maxShieldHP = MaxShield;
	movement = Move;
	accuracy = Acc;
	evasion = Evade;
	testWeapon = weapon;
	Location.x = x/32;
	Location.y = y/32;
}

int Ship::getHull() {
	return currentHullHP;
}

void Ship::Render() {
	//Text HPText(Game::renderer, "assets/bahnschrift.ttf.ttf", 10, "test", white);
	//UIFunciton::RenderHPText(destRect.x + 64, destRect.y, "assets/Android.ttf", 10, "test", white);
	//HPText.display(destRect.x + 64, destRect.y, Game::renderer);
	UIFunciton::RenderHPBar(destRect.x + 64, destRect.y, -64, -5, ((float)currentHullHP / (float)maxHullHP), red, black);
	UIFunciton::RenderHPBar(destRect.x + 64, destRect.y-5, -64, -5, ((float)currentShieldHP / (float)maxShieldHP), blue, black);
	SDL_RenderCopyEx(Game::renderer, objectTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
	if (isActive) {
		SDL_RenderCopyEx(Game::renderer, outlineTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
	}
	if (isTarget) {
		SDL_RenderCopyEx(Game::renderer, targetedTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
	}
}