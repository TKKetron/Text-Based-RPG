#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iomanip>
#include <conio.h>
#include <math.h>
#include <vector>
#include <Windows.h>

#include "Player.h"
#include "Boss.h"

Player *player;

using namespace std;

int MenuSystem(vector<string> choice, string preText, string postText = "", int menu = 0);
void BackPack();
void MenuSelect();
void ChestRoom(int roomCount);
void MonsterRoom(int roomCount);

int main()
{
    srand(time(0));
    int roomCount = 0;
    Item* startWarrior;
    Item* startRanger;

    

    cout << "Hello, Welcome to the dungeon Crawl!\n";
    cout << "Would you like to be a (0)Warrior or (1)Ranger?\n";
    cout << " Stat |Warrior | Ranger |\n";
    cout << "  HP  |   15   |   10   |\n";
    cout << "Armor |   7    |   5    |\n";
    cout << "Weapon| Sword  |  Bow   |\n";
    cout << " Util | Poison |  Food  |\n";
    int select = 0;
    bool confirm = false;
    select = MenuSystem
    (
        {"Warrior","Ranger "},
        "Hello, Welcome to the dungeon Crawl!\nWould you like to be a Warrior or Ranger?\n\n'SPACE' to confirm | 'A' or 'D' to change selection |\n Stat |Warrior | Ranger |\n  HP  |   15   |   10   |\nArmor |   7    |   5    |\nWeapon| Sword  |  Bow   |\n Util | Poison |  Food  |\n\n",
        ""
    );

    

    startWarrior = new Item[2]{ { sword, 5 },{ poison, 5 } };
    startRanger = new Item[3]{ { bow, 6 },{ food, 5 },{ food, 8 } };

    if(select)
        player = new Player(10, 15, 3, 2, 5, startRanger, 3, true);
    else
        player = new Player(15, 0, 4, 3, 5, startWarrior, 2, false);
    delete[] startRanger, startWarrior;

    select ? cout << "you have chosen Ranger\n" : cout << "you have chosen Warrior\n";
    system("pause");
    do
    {
        roomCount++;
        MenuSelect();
        system("cls");
        switch (rand() % 6)
        {
        case 0:
            ChestRoom(roomCount);
            break;
        default:
            MonsterRoom(roomCount);
        }
        system("pause");
    }while (player->GetHP() > 0);
    system("cls");
    cout << "You survived " << roomCount << " rooms";
    delete player;
    return 0;
}

int MenuSystem(vector<string> choice, string preText, string postText, int menu)
{
    int select = 0;
    int chCount = choice[0].size()+4;
    while (true)
    {
        system("cls");
        cout << preText;
        cout << setfill(' ') << setw((select)*chCount + chCount) << string(chCount, '-') << endl;
        for (int i = 0; i < choice.size(); i++)
            if (i == select)
                printf("| %s |", choice[i].c_str());
            else
                printf("  %s  ", choice[i].c_str());
        cout << endl << setfill(' ') << setw((select)*chCount + chCount) << string(chCount, '-') << endl;
        switch (menu)
        {
        case 1:
            switch (player->GetItems()[select].type)
            {
            case sword:
                printf("This is your sword it does %d damage to enemies with no armor\n", player->GetItems()[select].value);
                break;
            case bow:
                printf("This is your bow it does %d damage to enemies with no armor if you have arrows\n", player->GetItems()[select].value);
                break;
            case poison:
                printf("This is a Poison Potion it does %d damage to ALL enemies ignoring armor\n", player->GetItems()[select].value);
                break;
            case food:
                printf("This food will heal you %d HP if you eat it\n", player->GetItems()[select].value);
                break;
            case NONE:
                printf("This slot in your backpack is EMPTY\n");
                break;
            }
        default:
            cout << postText;
        }
        switch (_getch())
        {
        case 'd':
            if (select < choice.size() - 1)
                select++;
            break;
        case 'a':
            if (select > 0)
                select--;
            break;
        case ' ':
            system("cls");
            return select;
        case 27:
            return -1;
        }
    }
    
}

void MenuSelect()
{
    int select = 0;
    bool confirm;
    do
    {
        select = MenuSystem
        (
            { "Continue","Backpack" },
            string("STATS: HP ") + to_string(player->GetHP()) + " | ARMOR " + to_string(player->GetChest() + player->GetHel()) + " | ARROWS " + to_string(player->GetAmmo()) + " | \n'SPACE' to confirm | 'A' or 'D' to change selection | \nwould you like to continue or look at your backpack?\n",
            ""
        );
        if (select == 0)
            return;
        BackPack();
        
    } while (true);
    
}

void BackPack()
{
    int select = 0;
    do
    {
        select = MenuSystem
        (
            { 
                ItemTypeS[player->GetItems()[0].type].c_str(),
                ItemTypeS[player->GetItems()[1].type].c_str(),
                ItemTypeS[player->GetItems()[2].type].c_str(),
                ItemTypeS[player->GetItems()[3].type].c_str(),
                ItemTypeS[player->GetItems()[4].type].c_str()
            },
            string("STATS: HP ") + to_string(player->GetHP()) + " | ARMOR " + to_string(player->GetChest() + player->GetHel()) + " | ARROWS " + to_string(player->GetAmmo()) + " | \n'SPACE' to confirm | 'A' or 'D' to change selection | \nHere is your Inventory: \n",
            "",
            1
        );
        if (select == -1)
            return;
        
        switch (player->GetItems()[select].type)
        {
        case food:
            printf("You ate food and healed %d HP you total HP was %d and is now ", player->GetItems()[select].value, player->GetHP());
            player->UseItem(select);
            cout << player->GetHP() << endl;
            break;
        case NONE:
            cout << "No item in this slot select something else or press 'ESC' to leave\n";
            break;
        default:
            cout << "You are not in combat you cant use that right now.\n";
            break;
        }

        system("pause");
    } while (select >= 0);

    
}

void ChestRoom(int roomCount)
{
    short select = MenuSystem
        (
            {
                "  OPEN  ",
                "Continue"
            },
            "As you enter the room before you lies a chest in the center, Would you like to open it or continue on?\n"
        );
    

    if (select == 1)
    {
        cout << "You decide to continue onwards without opening the chest, you wonder what could have been inside\n";
        return;
    }
    rand() % 5 == 0 ? select = 1 : select = 0;
    if (select)
    {
        int damage = floor(sqrt(roomCount) / 3 * (rand() % 10) + 3);
        player->Damage(player->GetChest() + player->GetHel() + damage);
        printf("You decide to open the chest and find it was trapped, you take %d damage, Your HP is now %d\n", damage, player->GetHP());
        return;
    }
    int arrow = rand() % 10+1;
    printf("You open the chest and find %d arrows, they have been added to your inventory\n", arrow);
    system("pause");
    system("cls");
    player->AddAmmo(arrow);
    pair<Item*, int> loot = Globals::RandomChest(roomCount,player->GetRanger());
    for (int i = 0; i < loot.second; i++)
    {
        bool swap = false;
        printf("You look in the chest to see if there are any more items an you find a %s\n", ItemTypeS[loot.first[i].type].c_str());
        system("pause");
        if (loot.first[i].type == helmet )
        {
            select = MenuSystem
            (
                {
                "No ",
                "Yes"
                },
                "Do you want to change your " + ItemTypeS[loot.first[i].type] + " with " + to_string(player->GetHel())  + " defense for one with " + to_string(loot.first[i].value) + "\n",
                ""
            );
            if (select)
                    player->ChangeArmor(true, loot.first[i].value);
        }
        else if(loot.first[i].type == chestplate)
        {
            select = MenuSystem
            (
                {
                "No ",
                "Yes"
                },
                "Do you want to change your " + ItemTypeS[loot.first[i].type] + " with " + to_string(player->GetChest()) + " defense for one with " + to_string(loot.first[i].value) + "\n",
                ""
            );
            if (select)
                player->ChangeArmor(false, loot.first[i].value);
        }
        else
        {
            do
            {
                select = MenuSystem
                (
                    {
                    ItemTypeS[player->GetItems()[0].type].c_str(),
                    ItemTypeS[player->GetItems()[1].type].c_str(),
                    ItemTypeS[player->GetItems()[2].type].c_str(),
                    ItemTypeS[player->GetItems()[3].type].c_str(),
                    ItemTypeS[player->GetItems()[4].type].c_str()
                    },
                    "STATS: HP " + to_string(player->GetHP()) + " | ARMOR " + to_string(player->GetChest() + player->GetHel()) + " | ARROWS " + to_string(player->GetAmmo()) + " | \n'SPACE' to confirm | 'A' or 'D' to change selection | `esc` to keep current items |\nHere is your Inventory: \n",
                    "\nSelect item to be changed",
                    1
                );
                if (select == -1)
                    break;
                swap = MenuSystem
                (
                    {
                        "No ",
                        "Yes"
                    },
                    "Do you want to swap " + ItemTypeS[player->GetItems()[select].type] + "(" + to_string(player->GetItems()[select].value) + ") for a " + ItemTypeS[loot.first[i].type] + "(" + to_string(loot.first[i].value) + ")\n",
                    ""
                );
            } while (!swap);
            if(select != -1)
                player->ChangeItem(select, loot.first[i]);
        }
        system("cls");
    }
    cout << "You see nothing else in the chest and continue on\n";
    free(loot.first);
}
void MonsterRoom(int roomCount)
{
    Enemy* dudes;
    int select = 0;
    int numdudes = 1;
    bool boss = false;
    bool battle = true;
    bool rangAtk = false;
    switch (rand() % 20) 
    {
    case 0:
        boss = true; 
        break;
    case 1:
    case 2:
        numdudes = rand() % 1 + 2;
    }//decides the room

    if (!boss)
    {
        dudes = new Enemy[numdudes];
        for (int i = 0; i < numdudes; i++)
            dudes[i] = Enemy(roomCount);
    } //init if boss
    else
    {
        dudes = new Boss(roomCount);
    }//init if dudes

    if (boss)
        cout << "You enter the room and before you stands a boss.\n";
    else if (numdudes == 1)
        cout << "You enter the room and before you stands 1 enemy.\n";
    else
        cout << "You enter the room and before you stands " << numdudes << " enemies.\n";
    system("Pause");
    system("cls");

    bool playerT = false;//rand() % 2;//decides who goes first
    do
    {
        playerT = !playerT;
        if (playerT)
        {
            rangAtk = false;
            bool attack = false;
            do
            {
                do
                {
                    select = MenuSystem
                    (
                        {
                            "BackPack",
                            "  Run   "
                        },
                        "Would You like to use an item or run?\n"
                    );
                } while (select == -1);
                if (select == 1)
                    if (rand() % 2 == 0)
                    {
                        numdudes = -1;
                        break;
                    }
                    else
                    {
                        cout << "You did not get away\n";
                        system("pause");
                        continue;
                    }

                battle = false;//assume the player won

                //Backpack code
                do
                {
                    select = MenuSystem
                    (
                        {
                            ItemTypeS[player->GetItems()[0].type].c_str(),
                            ItemTypeS[player->GetItems()[1].type].c_str(),
                            ItemTypeS[player->GetItems()[2].type].c_str(),
                            ItemTypeS[player->GetItems()[3].type].c_str(),
                            ItemTypeS[player->GetItems()[4].type].c_str()
                        },
                        string("STATS: HP ") + to_string(player->GetHP()) + " | ARMOR " + to_string(player->GetChest() + player->GetHel()) + " | ARROWS " + to_string(player->GetAmmo()) + " | \n'SPACE' to confirm | 'A' or 'D' to change selection | \nHere is your Inventory: \n",
                        "",
                        1
                    );

                    switch (player->GetItems()[select].type)
                    {
                    case food:
                        printf("You ate food and healed %d HP you total HP was %d and is now ", player->GetItems()[select].value, player->GetHP());
                        player->UseItem(select);
                        cout << player->GetHP() << endl;
                        break;
                    case NONE:
                        cout << "No item in this slot select something else or press 'ESC' to leave\n";
                        break;
                    case bow:
                        if (player->GetAmmo() <= 0)
                        {
                            cout << "You are out of ammo please select another option\n";
                            system("pause");
                            select = -1;
                        }
                        else
                            attack = true;
                        break;
                    default:
                        attack = true;
                    }
                } while (player->GetItems()[select].type == NONE);
                    
            } while (select == -1);
            
            if (!attack)
                continue;
            vector<string> goonText;
            for (int i = 0; i < numdudes; i++)
                if (dudes[i].GetHP() > 0)
                    goonText.push_back("Enemy" + to_string(i));
            int goonChoice;

            do
            {
                goonChoice = MenuSystem
                (
                    goonText,
                    "Which enemy would you like to attack?\n"
                );
            } while (goonChoice == -1);
            if (dudes[goonChoice].GetRanged())
                if (rand() % 4 == 0)
                {
                    cout << "Your attack missed\n";
                    battle = true;
                    continue;
                }
            dudes[goonChoice].Damage(player->GetItems()[select].value);
            if (dudes[goonChoice].GetDef() > player->GetItems()[select].value)
                cout << "The monsters defence is too high for your attack\n";
            else
                printf("Enemy %d took %d damage\n", goonChoice, player->GetItems()[select].value - dudes[goonChoice].GetDef());
            if (player->GetItems()[select].type == bow)
            {
                player->AddAmmo(-1);
                rangAtk = true;
            }




            for (int i = 0; i < numdudes; i++) //checks if player did win
                if (dudes[i].GetHP() > 0)
                {
                    battle = true;
                    break;
                }
            system("pause");
        }
        else//dudes turn
        {
            system("cls");
            cout << "The enemies have begun attacking\n";
            
            for (int i = 0; i < numdudes; i++)
            {
                if (rangAtk)
                    if (rand() % 4 == 0)
                    {
                        printf("Enemy %d missed\n", i);
                        continue;
                    }
                player->Damage(dudes[i].Attack());
                if (player->GetChest() + player->GetHel() > dudes[i].Attack())
                    printf("You defense is too high for enemy %d\n",i);
                else
                    printf("Enemy %d did %d damage. Your HP is now %d\n", i, dudes[i].Attack(), player->GetHP());
            }
                
            system("pause");
            


            if (player->GetHP() <= 0)//checks if player is ded
            {
                cout << "You have died\n";
                return;
            }
        }
        
    } while (battle && numdudes != -1);
    //battle won OVER

    system("cls");

    //loot
    if (numdudes == -1)
    {
        cout << "You got away successfully\n";
    }
    else if (boss)
    {
        printf("you have defeated the boss, he dropped the following loot\n");
        system("pause");
        for (int i = 0; i < dudes[0].GetLootAmount(); i++)
        {
            system("cls");
            bool swap = false;
            printf("you find a %s\n", ItemTypeS[dudes->GetLoot()[i].type].c_str());
            system("pause");
            if (dudes->GetLoot()[i].type == helmet)
            {
                select = MenuSystem
                (
                    {
                    "No ",
                    "Yes"
                    },
                    "Do you want to change your " + ItemTypeS[dudes->GetLoot()[i].type] + " with " + to_string(player->GetHel()) + " defense for one with " + to_string(dudes->GetLoot()[i].value) + "\n",
                    ""
                );
                if (select)
                    player->ChangeArmor(true, dudes->GetLoot()[i].value);
            }
            else if (dudes->GetLoot()[i].type == chestplate)
            {
                select = MenuSystem
                (
                    {
                    "No ",
                    "Yes"
                    },
                    "Do you want to change your " + ItemTypeS[dudes->GetLoot()[i].type] + " with " + to_string(player->GetChest()) + " defense for one with " + to_string(dudes->GetLoot()[i].value) + "\n",
                    ""
                );
                if (select)
                    player->ChangeArmor(false, dudes->GetLoot()[i].value);
            }
            else
            {
                do
                {
                    select = MenuSystem
                    (
                        {
                        ItemTypeS[player->GetItems()[0].type].c_str(),
                        ItemTypeS[player->GetItems()[1].type].c_str(),
                        ItemTypeS[player->GetItems()[2].type].c_str(),
                        ItemTypeS[player->GetItems()[3].type].c_str(),
                        ItemTypeS[player->GetItems()[4].type].c_str()
                        },
                        "STATS: HP " + to_string(player->GetHP()) + " | ARMOR " + to_string(player->GetChest() + player->GetHel()) + " | ARROWS " + to_string(player->GetAmmo()) + " | \n'SPACE' to confirm | 'A' or 'D' to change selection | \nHere is your Inventory: \n",
                        "\nSelect item to be changed",
                        1
                    );
                    if (select == -1)
                    {
                        system("cls");
                        break;
                    }
                    swap = MenuSystem
                    (
                        {
                            "No ",
                            "Yes"
                        },
                        "Do you want to swap " + ItemTypeS[player->GetItems()[select].type] + "(" + to_string(player->GetItems()[select].value) + ") for a " + ItemTypeS[dudes->GetLoot()[i].type] + "(" + to_string(dudes->GetLoot()[i].value) + ")\n",
                        ""
                    );
                } while (!swap);
                if(select != -1)
                    player->ChangeItem(select, dudes->GetLoot()[i]);
            }
        }
        cout << "You find no more loot\n";
    }
    else
        cout << "You have defeated all the enemies\n";
    
    
    if (boss)
        delete dudes;
    else
        delete[] dudes;
}

/*
* 2 rooms:
*   chest(1/6):
*       mimic(1/5): take flat damage 
*       loot: sword (1/2 if warrior 1/8 if ranger), bow (1/2 if ranger 1/8 if warrior), potion (1/16), food (1/8), 1/8 helmet, 1/16 chestplate
*   Monster(5/6):
*       normal(17/20): 1 standard enemy
*       MINI Boss(1/10) 2-5 standard enemies
*       Boss(1/20) - 1 big baddie who with 3 chests
*/