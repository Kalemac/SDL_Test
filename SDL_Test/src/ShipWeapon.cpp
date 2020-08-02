#include "ShipWeapon.h"

bool ShipWeapon::checkArcRange(int relativeAngle, int targetRange)
{
std:cout << " RA = " << relativeAngle << " Weapon arc = " << arc.startAngle << " " << arc.endAngle << " Range = " << targetRange << " MaxRange = " << range << std::endl;
	if (arc.startAngle < 0 && arc.endAngle > 0)
	{
		if (relativeAngle >= (arc.startAngle + 360) || relativeAngle <= arc.endAngle)
		{
			if (targetRange <= range)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		if ((relativeAngle >= arc.startAngle) && (relativeAngle <= arc.endAngle))
		{
			if (targetRange <= range)
			{
				return true;
			}
		}
			return false;
	}
	return false;
}

ShipWeapon::ShipWeapon(int mD, int MD, FiringArc farc, int r, DamageType t)
{
	minDamage = mD;
	maxDamage = MD;
	arc = farc;
	range = r;
	type = t;
}
