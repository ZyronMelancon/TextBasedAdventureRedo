#pragma once
#include "string.h"

//Command data
string dir[4] = {
	dir[0] = "up",
	dir[1] = "down",
	dir[2] = "left",
	dir[3] = "right"
};

string com[5] = {
	com[0] = "item",
	com[1] = "attack",
	com[2] = "talk",
	com[3] = "pickup",
	com[4] = "move"
};


//Room-specific dialogue
string dial[10] = {
	dial[0] = "It's a pretty empty room... Maybe I should explore.",
	dial[1] = "This room has the same emptiness as the first...\nBut there's a chest! Maybe if I have a key...",
	dial[2] = "As I walk into this room, it seems I am not alone.\nThe winged being in the room looks over to me with a\nhopeful gaze. It seems as if it wants to speak.",
	dial[3] = "The room is full of light. In the center seems\nto be a glowing orb. It radiates a peaceful\naura.",
	dial[4] = "Immediately after entering the room, I feel my\nenergy being drained! I see random patches...\nI should probably get out before I can't move.",
	dial[5] = "I step into a strange gelatinous substance...\nThe stuff is all over! Strangely, I feel as \nif I am healing. I wonder what this means.",
	dial[6] = "This room is quite empty, but there are many\ndoors. The east-most door is rather large and\nhas a keyhole.",
	dial[7] = "I see a pedistal in the center of the room. \nOn closer examination, it seems to have a slot\nfor the glowing orb I received earlier.",
	dial[8] = "The sylph and fairy seem happy to be together\nagain. They await my actions.",
	dial[9] = "The dark forces have been defeated. The room\nis now peaceful and empty."
};

//Sprites
string spr[5] = {
	spr[0] = ".oOo.",
	spr[1] = ".o.",
	spr[2] = "0o.."
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
Item gelPotion = { "Bottled Gel", "l", 1, 50, true };
Item bottle = { "Bottle", "i", 0, 0, true };
Item fairy = { "Little Fairy", "+", 0, 0, true };
Item blank = { "N/A", " ", 0, 0, false };


//Player data
struct Player
{
	int health;
	Item inv[3];
};

Player player = { 100, blank, blank, blank };