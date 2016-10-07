#pragma once
#include "string.h"

//Command data
string dir[4] = {
	dir[0] = "up",
	dir[1] = "down",
	dir[2] = "left",
	dir[3] = "right"
};

string com[3] = {
	com[0] = "attack",
	com[1] = "item",
	com[2] = "run"
};


//Room-specific dialogue
string dial[9] = {
	dial[0] = "It's a pretty empty room... I found a bottle here.\nMaybe it will be useful.",
	dial[1] = "This room has the same emptiness as the first...\nBut there's a chest! Maybe if I have a key...",
	dial[2] = "As I walk into this room, it seems I am not alone.\nThe being looks over at me with a hopeful gaze.",
	dial[3] = "The room is full of light. In the center is seems\nto be a glowing orb. It radiates a peaceful\naura.",
	dial[4] = "Immediately after entering the room, I feel my\nenergy being drained! I see two dark figures...\nI should probably get out before I can't move.",
	dial[5] = "I step into a strange gelatinous substance...\nThe stuff is all over! Strangely, I feel as \nif I am healing. I wonder what this means.",
	dial[6] = "This room is quite empty, but there are many\ndoors. The east-most door is rather large and\nhas a keyhole.",
	dial[7] = "I see a pedistal in the center of the room. \nOn closer examination, it seems to have a slot\nfor the glowing orb I received earlier."
};

//Room data
struct Room
{
	bool up;
	bool down;
	bool left;
	bool right;
	int type;
	bool locked;
	int locktype;
};

Room room[9] = {
	room[0] = { true, false, false, true, 0, false },
	room[1] = { true, false, true, false, 1, false },
	room[2] = { true, false, false, true, 2, false },
	room[3] = { false, false, true, false, 3, true, 2 },
	room[4] = { false, true, false, false, 4, false },
	room[5] = { false, true, false, true, 5, false },
	room[6] = { false, true, true, true, 6, false },
	room[7] = { false, false, true, true, 7, true, 3 },
	room[8] = { false, false, false, false, 8, true, 4 }
};


//Item data
struct Item
{
	string name;
	string sprite;
	int type;
	int effect;
	bool deplete;
};

Item key[3] = {
	key[0] = { "Chest Key", "o-=", 4 },
	key[1] = { "Sylph's Key", "@=~", 3 },
	key[2] = { "Room Key", "O=v", 2 }
};
Item glowOrb = { "Glowing Orb", "o", 1, 40, false };
Item gelPotion = { "Bottled Gel", "l", 0, 50, true };
Item bottle = { "Bottle", "i", 5, 0, true };


//Player data
struct Player
{
	int health;
	Item inv1;
	Item inv2;
};

Player player = { 100, bottle };