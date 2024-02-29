#pragma once

#include <string>

enum ItemType
{
	sword = 0,
	bow,
	poison,
	food,
	helmet,
	chestplate,
	NONE
};
static std::string ItemTypeS[10] =
{
	"  Sword   ",
	"   Bow    ",
	"  Poison  ",
	"   Food   ",
	"  Helmet  ",
	"Chestplate",
	"  EMPTY   "
};
struct Item
{
	ItemType type;
	int value;
	bool operator==(const Item& compare)
	{
		return type == compare.type && value == compare.value;
	}
	bool operator!=(const Item& compare)
	{
		return type != compare.type || value != compare.value;
	}
};

static Item blank{ NONE,0 };

static class Globals
{
public: 
	static int Random(int max, int min);
	static std::pair<Item*, int> RandomChest(int roomLevel, bool ranger);
};

