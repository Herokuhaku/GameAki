#pragma once
#include "Trail.h"

struct HomingShot:
	public Bullet
{
	HomingShot();
	Trail trail;
};

