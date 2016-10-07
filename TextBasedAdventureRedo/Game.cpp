#include <iostream>
#include <Windows.h>
#include "string.h"
#include "resources.h"

int currentRoom = 0;
char *input = new char[256];

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

	
}

void listPlayerData()
{
	cursorPos(27, 2);
	printf("Player");
	cursorPos(27, 3);
	std::cout << "Health: " << player.health;
	cursorPos(27, 4);
	printf("Items");
	cursorPos(27, 5);
	std::cout << player.inv1.name.cstyle();
}

void dialogue(int n)
{
	cursorPos(0, 15);
	std::cout << dial[n].cstyle() << std::endl;
	printf("\n");
}

void userMove(int n)
{

	printf("Where would you like to go? (up, down, left, right)\n");
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
}

void main()
{
	while (true)
	{
		roomDraw(room[currentRoom]);
		listPlayerData();
		dialogue(currentRoom);
		userMove(currentRoom);
	}
	system("pause");
}