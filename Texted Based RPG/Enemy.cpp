#include "Enemy.h"

#include<math.h>
#include<stdlib.h>

Enemy::Enemy()
{
	hp = 0;
	def = 0;
	atk = 0;
	ranged = 0;
}

Enemy::Enemy(int hp, int def, int atk, bool ranged)
{
	this->hp = hp;
	this->def = def;
	this->atk = atk;
	this->ranged = ranged;
}

Enemy::Enemy(int room)
{
	ranged = rand() % 2;
	int dif = rand() % 20 + 1;
	hp = ceil(3.75 * log(dif * room) + 2.5 + dif / 10.0);
	def = floor((dif / 5.0 + 2) * log(room/2.0) + 2);
	atk = floor((dif / 10.0 + 2)*sqrt(room));
}

Enemy::Enemy(int room, bool boss)
{
	ranged = rand() % 2;
	int dif = rand() % 5 + 15;
	hp = ceil(dif/3.5 * log(1.5*dif * room) + dif / 4.0);
	def = floor((dif / 5.0 + 2) * log(room) + 2);
	atk = floor((dif / 10.0 + 2) * sqrt(room));
}

void Enemy::Copy(Enemy copy)
{
	hp = copy.GetHP();
	atk = copy.Attack();
	ranged = copy.GetRanged();
	def = copy.GetDef();
}
int Enemy::Attack()
{
	return atk;
}
void Enemy::Damage(int damage)
{
	if (damage > def)
		hp -= damage - def;
}
bool Enemy::GetRanged()
{
	return ranged;
}

int Enemy::GetHP()
{
	return hp;
}

int Enemy::GetDef()
{
	return def;
}

Item* Enemy::GetLoot()
{
	return &blank;
}
int Enemy::GetLootAmount()
{
	return 0;
}
