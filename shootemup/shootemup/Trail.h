#pragma once
#include <list>
#include "Bullet.h"

struct HomingShot;

class Trail
{
public:
	Trail(HomingShot& owner);
	~Trail() {};
	void Update(void);
	void Draw(void);
	void Clear(void);
	void SetHandle(int handle);
private:
	HomingShot& owner_;
	// À•W‚Ì—š—ğ
	std::list<Position2> history_;
	int handle_;
};

