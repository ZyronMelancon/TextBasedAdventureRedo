#include <iostream>
#include <Windows.h>
#include "string.h"
#include "resources.h"

int currentRoom = 0;
char *input = new char[256];
int input2;
bool havechestkey = false;
bool havesylphkey = false;
bool havedoorkey = false;
bool gavefairy = false;
bool havebottle = false;
bool defeated = false;
bool gameover = false;
bool win = false;
bool haveorb = false;
bool orbplaced = false;

void cursorPos(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void roomDraw(Room room)
{
	system("cls");
	cursorPos(0, 0);
	printf("_________________________\n");
	for (int i = 0; i < 10; i++)
		printf("|                       |\n");
	printf("_________________________\n");

	if (room.up)
	{
		cursorPos(12, 1);
		printf("^");
	}
	if (room.down)
	{
		cursorPos(12, 10);
		printf("v");
	}
	if (room.left)
	{
		cursorPos(1, 5);
		printf("<");
	}
	if (room.right)
	{
		cursorPos(23, 5);
		printf(">");
	}

	if (currentRoom == 5)
	{
		cursorPos(1, 5);
		std::cout << spr[2].cstyle();
		cursorPos(5, 3);
		std::cout << spr[0].cstyle();
		cursorPos(10, 7);
		std::cout << spr[0].cstyle();
		cursorPos(14, 4);
		std::cout << spr[1].cstyle();
		cursorPos(3, 9);
		std::cout << spr[1].cstyle();
	}

	if (currentRoom == 1)
	{
		cursorPos(17, 7);
		printf(" ___ ");
		cursorPos(17, 8);
		printf("|_._|");
		cursorPos(17, 9);
		printf("|___|");
	}

	if (currentRoom == 2)
	{
		cursorPos(3, 8);
		printf("X");
	}
	if (currentRoom == 2 && gavefairy == true)
	{
		cursorPos(3, 7);
		printf("+");
	}

	if (currentRoom == 6 && havechestkey == false)
	{
		cursorPos(20, 2);
		std::cout << key[0].sprite.cstyle();
	}
	
	if (currentRoom == 0 && havebottle == false)
	{
		cursorPos(2, 10);
		std::cout << bottle.sprite.cstyle();
	}

	if (currentRoom == 3 && haveorb == false)
	{
		cursorPos(13, 5);
		printf("v");
		cursorPos(12, 6);
		printf(">o<");
		cursorPos(13, 7);
		printf("^");
	}

	if (currentRoom == 7 && orbplaced == false)
	{
		cursorPos(18, 5);
		printf("___");
		cursorPos(18, 6);
		printf("|_|");
	}
	else if (currentRoom == 7 && orbplaced == true)
	{
		cursorPos(19, 3);
		printf("v");
		cursorPos(18, 4);
		printf(">o<");
		cursorPos(18, 5);
		printf("_^_");
		cursorPos(18, 6);
		printf("|_|");
	}

	if (currentRoom == 4 && defeated == false)
	{
		for (int i = 1; i < 24; i++)
		{
			for (int o = 1; o < 10; o++)
			{
				cursorPos(i, o);
				switch (rand() % 2)
				{
				case 0:
					printf(" ");
					break;
				case 1:
					printf("#");
					break;
				}
			}
		}
	}
	else if (currentRoom == 4 && defeated == true && havedoorkey == false)
	{
		cursorPos(12, 5);
		std::cout << key[2].sprite.cstyle();
	}
}

void listPlayerData()
{
	cursorPos(27, 2);
	printf("Player");
	cursorPos(27, 4);
	std::cout << "Health: " << player.health;
	cursorPos(27, 5);
	printf("Items: ");
	cursorPos(27, 6);
	std::cout << player.inv[0].name.cstyle();
	cursorPos(27, 7);
	std::cout << player.inv[1].name.cstyle();
	cursorPos(27, 8);
	std::cout << player.inv[2].name.cstyle();

	cursorPos(40, 2);
	printf("Actions");
	cursorPos(40, 4);
	printf("item");
	cursorPos(40, 5);
	printf("attack");
	cursorPos(40, 6);
	printf("talk");
	cursorPos(40, 7);
	printf("pickup");
	cursorPos(40, 8);
	printf("move [direction]");
}

void dialogue(int n)
{
	cursorPos(0, 15);
	if (currentRoom == 2 && gavefairy == true)
		std::cout << dial[8].cstyle() << std::endl;
	else if (currentRoom == 4 && defeated == true)
		std::cout << dial[9].cstyle() << std::endl;
	else if (currentRoom == 8)
		printf("\n");
	else
		std::cout << dial[n].cstyle() << std::endl;
	printf("\n");
}

void userMove(int n)
{
	//printf("Where would you like to go? (up, down, left, right)\n");
	std::cin >> input;

	if (dir[0].strcomp(input) && room[n].up && room[n + 4].locked == false)
		currentRoom = currentRoom + 4;
	else if (dir[1].strcomp(input) && room[n].down && room[n - 4].locked == false)
		currentRoom = currentRoom - 4;
	else if (dir[2].strcomp(input) && room[n].left && room[n - 1].locked == false)
		currentRoom--;
	else if (dir[3].strcomp(input) && room[n].right && room[n + 1].locked == false)
		currentRoom++;
	else if (dir[3].strcomp(input) && room[n].right && room[n + 1].locked)
	{
		printf("That room is locked! Maybe if I had a key...\n");
		system("pause");
	}
	else
	{
		printf("Invalid input!\n");
		system("pause");
	}

	if (currentRoom == 4 && defeated == false)
	{
		player.health = player.health - 10;
	}
}

void action()
{
	printf("What would you like to do?\n");
	std::cin >> input;

	if (com[0].strcomp(input))
	{
		printf("Which item?\n");
		std::cout << "1. " << player.inv[0].name.cstyle() << std::endl;
		std::cout << "2. " << player.inv[1].name.cstyle() << std::endl;
		std::cout << "3. " << player.inv[2].name.cstyle() << std::endl;
		std::cin >> input2;

		if (bottle.name.strcomp(player.inv[input2-1].name) && currentRoom == 5)
		{
			printf("I bottle the strange gel. At this point, any\nidea should be tested.\n");
			system("pause");
			player.inv[input2-1] = gelPotion;
		}
		else if (key[0].name.strcomp(player.inv[input2-1].name) && currentRoom == 1)
		{
			printf("The chest opens! A little fairy flies out and\nimmediately tucks itself into my shirt's pocket.\nIt seems too scared to come out...\n");
			system("pause");
			player.inv[input2-1] = fairy;
		}
		else if (key[1].name.strcomp(player.inv[input2-1].name) && currentRoom == 2)
		{
			printf("The large door opens! I can walk inside now.\n");
			system("pause");
			player.inv[input2-1] = blank;
			room[3].locked = false;
		}
		else if (key[2].name.strcomp(player.inv[input2-1].name) && currentRoom == 6)
		{
			printf("The large door opens! I can walk inside now.\n");
			system("pause");
			player.inv[input2-1] = blank;
			room[7].locked = false;
		}
		else if (gelPotion.name.strcomp(player.inv[input2-1].name))
		{
			printf("I drink the mysterious gel. It tasted horrible.\n...A moment after, I feel myself heal and regain energy.\n");
			system("pause");
			player.inv[input2 - 1] = bottle;
			player.health = 100;
		}
		else if (fairy.name.strcomp(player.inv[input2 - 1].name) && currentRoom == 2)
		{
			printf("I lightly nudge my pocket for the fairy to come\nout. Upon seeing its friend, it flies out and\nreunites. The sylph thanks me, gifting a key in return.\n");
			system("pause");
			player.inv[input2 - 1] = key[1];
			gavefairy = true;
		}
		else if (glowOrb.name.strcomp(player.inv[input2 - 1].name) && currentRoom == 4)
		{
			printf("The glowing orb suddenly flashes bright! The\nlight overpowers the dark energy, making it\ndissipate. A key is left behind.\n");
			system("pause");
			defeated = true;
		}
		else if (glowOrb.name.strcomp(player.inv[input2 - 1].name) && currentRoom == 7)
		{
			printf("I place the glowing orb on the pedistal, and\nthe door behind it opens up on its own.\nI see light!\n");
			system("pause");
			room[8].locked = false;
			orbplaced = true;
		}
		else
		{
			printf("I can't use that here!\n");
			system("pause");
		}
	}

	else if (com[1].strcomp(input))
	{
		if (currentRoom == 4 && defeated == false)
		{
			switch (rand() % 2)
			{
			case 0:
				printf("D O  N O T  R E S I S T  O U R  P O W E R .\n");
				player.health = player.health - 20;
				system("pause");
				break;
			case 1:
				printf("I T ' S  N O  U S E .\n");
				player.health = player.health - 20;
				system("pause");
				break;
			}
		}
		else
		{
			printf("There is nothing for me to attack here!\n");
		}
	}

	else if (com[2].strcomp(input))
	{
		if (currentRoom == 2)
		{
			printf("The sylph expresses worry and sadness for a friend\nthat they cannot find... They request for help.\n");
			system("pause");
		}
		if (currentRoom == 4 && defeated == false)
		{
			switch (rand() % 2)
			{
			case 0:
				printf("D O  N O T  R E S I S T  O U R  P O W E R .\n");
				player.health = player.health - 20;
				system("pause");
				break;
			case 1:
				printf("I T ' S  N O  U S E .\n");
				player.health = player.health - 20;
				system("pause");
				break;
			}
		}
		else
			printf("There's no one to talk to but myself here...\n");
	}

	else if (com[3].strcomp(input))
	{
		if (currentRoom == 0 && havebottle == false)
		{
			printf("I found a bottle! This may be useful.\n");
			system("pause");
			player.inv[0] = bottle;
			havebottle = true;
		}
		else if (currentRoom == 6 && havechestkey == false)
		{
			printf("I found a key! It's pretty small...\n");
			system("pause");
			player.inv[1] = key[0];
			havechestkey = true;
		}
		else if (currentRoom == 3 && haveorb == false)
		{
			printf("I pick up the glowing orb. I am given a sense\nof peace and comfort.\n");
			system("pause");
			player.inv[1] = glowOrb;
			haveorb = true;
		}
		else if (currentRoom == 4 && defeated == true && havedoorkey == false)
		{
			printf("I pick up the key left behind. This must go\nto the last locked door.\n");
			system("pause");
			player.inv[2] = key[2];
			havedoorkey = true;
		}
		else
		{
			printf("There is nothing to pick up here!\n");
			system("pause");
		}
	}

	else if (com[4].strcomp(input))
	{
		userMove(currentRoom);
	}
}

void checkDeath()
{
	if (player.health <= 0)
		gameover = true;
}

void checkWin()
{
	if (currentRoom == 8)
	{
		gameover = true;
		win = true;
	}
}

void gameoverseq()
{
	if (gameover == true && win == false)
	{
		system("cls");
		cursorPos(13, 5);
		printf("YOU DIED");
		cursorPos(2, 7);
	}
	if (gameover == true && win == true)
	{
		printf("I step outside and take a breath of fresh air.\nI am free.\n");
		system("pause");
		system("cls");
		cursorPos(13, 5);
		printf("THE END");
		cursorPos(2, 7);
	}
}

void main()
{
	while (!gameover)
	{
		roomDraw(room[currentRoom]);
		listPlayerData();
		dialogue(currentRoom);
		action();
		checkDeath();
		checkWin();
	}

	gameoverseq();

	system("pause");
}