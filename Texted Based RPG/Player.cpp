#include "Player.h"
#include <iostream>
#include <stdlib.h>


Player::Player(int hp, int ammo, int chest, int head, int invSize, Item* startingItems, int itemAmount, bool ranger)
{
	this->ranger = ranger;
	this->hp = hp;
	chestplate = chest;
	helmet = head;
	this->ammo = ammo;
	this->invSize = invSize;
	inv = (Item*)malloc(invSize * sizeof(Item));
	if (invSize < itemAmount)
		std::unexpected();
	for (int i = 0; i < itemAmount; i++)
		inv[i] = startingItems[i];
	for (int i = itemAmount; i < invSize; i++)
		inv[i] = blank;
}

Player::~Player()
{
	free(inv);
}

void Player::Damage(int damage)
{
	if(helmet+chestplate < damage)
		hp -= damage - (helmet + chestplate);
}
Item* Player::GetItems()
{
	return inv;
}
void Player::ChangeItem(int location, Item newItem)
{
	inv[location] = newItem;
}
int Player::UseItem(int location)
{
	
		switch (inv[location].type)
		{
		case sword:
			return inv[location].value;
			break;
		case bow:
			if (ammo > 0)
			{
				ammo--;
				return inv[location].value;
			}
			return 0;
			break;
		case poison:
			return inv[location].value;
			break;
		case food:
			hp += inv[location].value;
			ChangeItem(location, blank);
			return -1;
			break;
		};
	return -1;
}

void Player::ChangeArmor(bool helm, int newArmor)
{
	if (helm)
		helmet = newArmor;
	else
		chestplate = newArmor;
}


int Player::GetHel()
{
	return helmet;
}

int Player::GetChest()
{
	return chestplate;
}

int Player::GetHP()
{
	return hp;
}

bool Player::GetRanger()
{
	return ranger;
}

int Player::GetAmmo()
{
	return ammo;
}

void Player::AddAmmo(int amount)
{
	ammo += amount;
}

bool Player::HasItem(Item* item)
{
	for (int i = 0; i < invSize; i++)
		if (inv[i] == *item)
			return true;
	return false;
}