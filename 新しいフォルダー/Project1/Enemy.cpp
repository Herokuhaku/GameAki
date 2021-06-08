#include "Enemy.h"
#include "Player.h"

void Enemy::Ondamage(int damage)
{
	life_ -= damage;
}

void Enemy::Attack()
{
	player_->Ondamage(10);
}
