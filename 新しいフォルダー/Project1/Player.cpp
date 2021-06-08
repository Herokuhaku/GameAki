#include "Player.h"
#include "Enemy.h"
using namespace Battle;

void Battle::Player::Ondamage(int damage)
{
	life_ - damage;
}

void Battle::Player::Attack()
{
	enemy_->Ondamage(10);
}
