#pragma once
#include <list>
#include "Geometry.h"

struct HomingShot;

class Trail
{
public:
	Trail(HomingShot& owner);
	void Update(void);
	void Draw(void);
	void Clear(void);
private:
	HomingShot& owner_;
	// ���W�̗���
	std::list<Position2> history_;
};

