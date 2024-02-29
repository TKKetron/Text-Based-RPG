#pragma once
#include "Enemy.h";



class Boss
	: public Enemy
{
public:
	Boss(int room);
	~Boss() override;
	int GetHP();
	Item* GetLoot() override;
	int GetLootAmount() override;
private:
	Item* drops;
	int amount;
};

