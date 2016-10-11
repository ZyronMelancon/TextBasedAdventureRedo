#include <iostream>
#include <Windows.h>
#include "string.h"
#include "resources.h"
#include "actions.h"

void cursorPos(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void roomDraw(Room room) //Draws the room and all containing items or beings, along with arrows to point to available rooms
{
	system("cls");
	cursorPos(0, 0);
	printf("_________________________\n"); //Draw the outline of the room
	for (int i = 0; i < 10; i++)
		printf("|                       |\n");
	printf("|_______________________|\n");

	if (room.up) //If the room has a room in such direction, draw an arrow
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

	if (currentRoom == 5) //Draw gel in room 5
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

	if (currentRoom == 1) //Draw chest in room 1
	{
		cursorPos(17, 7);
		printf(" ___ ");
		cursorPos(17, 8);
		printf("|_._|");
		cursorPos(17, 9);
		printf("|___|");
	}

	if (currentRoom == 2) //Draw Sylph in room 2
	{
		cursorPos(3, 8);
		printf("X");
	}

	if (currentRoom == 2 && gavefairy == true) //Draw fairy if given
	{
		cursorPos(3, 7);
		printf("+");
	}

	if (currentRoom == 6 && havechestkey == false) //Draw chest key in room 6 if not picked up yet
	{
		cursorPos(20, 2);
		std::cout << key[0].sprite.cstyle();
	}
	
	if (currentRoom == 0 && havebottle == false) //Draw bottle in room 0 if not picked up yet
	{
		cursorPos(2, 10);
		std::cout << bottle.sprite.cstyle();
	}

	if (currentRoom == 3 && haveorb == false) //Draw orb in room 3 if not picked up yet
	{
		cursorPos(13, 5);
		printf("v");
		cursorPos(12, 6);
		printf(">o<");
		cursorPos(13, 7);
		printf("^");
	}

	if (currentRoom == 7 && orbplaced == false) //Draw pedistal in room 7
	{
		cursorPos(18, 5);
		printf("___");
		cursorPos(18, 6);
		printf("|_|");
	}
	else if (currentRoom == 7 && orbplaced == true) //Draw pedistal with orb on top if placed
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

	if (currentRoom == 4 && defeated == false) //If darkness isn't defeated, draw it
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
	else if (currentRoom == 4 && defeated == true && havedoorkey == false) //If darkness is defeated and key not picked up, draw key
	{
		cursorPos(12, 5);
		std::cout << key[2].sprite.cstyle();
	}
}

void listPlayerData() //List player health and items, and available actions
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

void dialogue(int n) //Write dialogue (description of room, etc) 
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

void action() 
{
	printf("What would you like to do?\n");
	std::cin >> input;

	if (com[0].strcomp(input))
	{
		itemUse();
	}

	else if (com[1].strcomp(input))
	{
		attackseq();
	}

	else if (com[2].strcomp(input))
	{
		talk();
	}

	else if (com[3].strcomp(input))
	{
		pickup();
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