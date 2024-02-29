#pragma once
#include "Globals.h"


class Enemy
{
public:
	Enemy();
	Enemy(int hp, int def, int atk, bool ranged);
	Enemy(int room);
	Enemy(int room, bool boss);
	virtual ~Enemy() = default;
	void Copy(Enemy copy);
	int Attack();
	void Damage(int damage);
	bool GetRanged();
	int GetHP();
	int GetDef();
	virtual Item* GetLoot();
	virtual int GetLootAmount();
private:
	int hp;
	int def;
	int atk;
	bool ranged;
};

