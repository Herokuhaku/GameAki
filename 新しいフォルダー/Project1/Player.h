#pragma once

class Enemy;

namespace Battle
{
	class Player
	{
	public:
		void Ondamage(int damage);
		void Attack();
	private:
		Enemy* enemy_;
		int life_;
	};
}