#include "Boss.h"

Boss::Boss(int room)
	:Enemy(room, true)
{
	int lootCount = rand()%3 + 1;
	int offSet = 0;
	amount = 0;
	std::pair<Item*, int>* lootArr = new std::pair<Item*, int>[lootCount];
	for (int i = 0; i < lootCount; i++)
	{
		lootArr[i] = Globals::RandomChest(room, GetRanged());
		amount += lootArr[i].second;
	}
	drops = (Item*)malloc(amount * sizeof(Item));
	for (int i = 0; i < lootCount; i++)
	{
		for (int j = 0; j < lootArr[i].second; j++)
			drops[j + offSet] = lootArr[i].first[j];
		offSet += lootArr[i].second;
		free(lootArr[i].first);
	}
	delete[] lootArr;
	

}

Boss::~Boss()
{
	free(drops);
}

int Boss::GetHP()
{
	return 2 * Enemy::GetHP();
}

Item* Boss::GetLoot()
{
	return drops;
}
int Boss::GetLootAmount()
{
	return amount;
}