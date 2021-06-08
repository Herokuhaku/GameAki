#pragma once
class Player;

namespace Battle {
	class Player;
	class Weapon;
	class Enemy;
}

class Enemy
{
public:
	void Ondamage(int damage);
	void Attack();
private:
	Battle::Player* player_;
	int life_;
};

