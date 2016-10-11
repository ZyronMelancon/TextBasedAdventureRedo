#pragma once
#include "resources.h"

int currentRoom = 0;
char *input = new char[256];
int input2;

void userMove(int n) //Called when input action is "move". Waits for input for direction
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

void itemUse()
{
	printf("Which item?\n");
	std::cout << "1. " << player.inv[0].name.cstyle() << std::endl;
	std::cout << "2. " << player.inv[1].name.cstyle() << std::endl;
	std::cout << "3. " << player.inv[2].name.cstyle() << std::endl;
	std::cin >> input2;

	if (bottle.name.strcomp(player.inv[input2 - 1].name) && currentRoom == 5)
	{
		printf("I bottle the strange gel. At this point, any\nidea should be tested.\n");
		system("pause");
		player.inv[input2 - 1] = gelPotion;
	}
	else if (key[0].name.strcomp(player.inv[input2 - 1].name) && currentRoom == 1)
	{
		printf("The chest opens! A little fairy flies out and\nimmediately tucks itself into my shirt's pocket.\nIt seems too scared to come out...\n");
		system("pause");
		player.inv[input2 - 1] = fairy;
	}
	else if (key[1].name.strcomp(player.inv[input2 - 1].name) && currentRoom == 2)
	{
		printf("The large door opens! I can walk inside now.\n");
		system("pause");
		player.inv[input2 - 1] = blank;
		room[3].locked = false;
	}
	else if (key[2].name.strcomp(player.inv[input2 - 1].name) && currentRoom == 6)
	{
		printf("The large door opens! I can walk inside now.\n");
		system("pause");
		player.inv[input2 - 1] = blank;
		room[7].locked = false;
	}
	else if (gelPotion.name.strcomp(player.inv[input2 - 1].name))
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

void attackseq()
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

void talk()
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

void pickup()
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