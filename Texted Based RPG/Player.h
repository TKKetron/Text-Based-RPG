#pragma once

#include "Globals.h"

class Player
{
public:
	Player(int hp, int ammo, int chest, int head, int invSize, Item* startingItems, int itemAmount, bool ranger);
	~Player();
	void Damage(int damage);
	Item* GetItems();
	void ChangeItem(int location, Item newItem);
	int UseItem(int location);
	void ChangeArmor(bool helm, int newArmor);
	int GetHel();
	int GetChest();
	int GetHP();
	bool GetRanger();
	int GetAmmo();
	void AddAmmo(int amount);
	bool HasItem(Item* item);
private:
	bool ranger;
	int hp;
	int helmet;
	int chestplate;
	int invSize;
	int ammo;
	Item* inv;
};