#include "Globals.h"
#include <stdlib.h>
#include <vector>

int Globals::Random(int max, int min)
{
	return rand() * (max + 1 - min) + min;
}

std::pair<Item*, int> Globals::RandomChest(int roomLevel, bool ranger)
{
	int itemCount = rand() % 3 + 1;
	Item* items = (Item*)malloc(itemCount * sizeof(Item));
	for (int i = 0; i < itemCount; i++)
	{
		switch (rand() % 16)
		{
		case 0:
		case 1:
			ranger ? items[i] = { sword,5 } : items[i] = { bow,5 };
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			!ranger ? items[i] = { sword,5 } : items[i] = { bow,5 };
			break;
		case 10:
		case 11:
			items[i] = { food,5 };
			break;
		case 12:
			items[i] = { poison,5 };
			break;
		case 13:
		case 14:
			items[i] = { helmet,5 };
			break;
		case 15:
			items[i] = { chestplate,5 };
			break;
		}
	}
	

	return std::make_pair(items, itemCount);
}
