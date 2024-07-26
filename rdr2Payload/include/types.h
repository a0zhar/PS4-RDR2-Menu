#pragma once
#ifndef _TYPES_HH
#define _TYPES_HH

#include "buttons.h"
#include <stdint.h>
typedef unsigned long int _size_t;


typedef void *Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

// Missing types
typedef Any AnimScene;
typedef Any Prompt;
typedef Any ItemSet;
typedef Any PersChar;
typedef Any PopZone;
typedef Any PropSet;
typedef Any Volume;


struct Vector2 {
	float x;
	float y;
};


struct Vector3 {
	float x, _padx;
	float y, _padY;
	float z, _padZ;
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;
};

struct Color {
	int r;
	int g;
	int b;
	int a;
};

enum Font {
	Arial,
	Cabrito,
	DroidSerif,
	Hapna,
	Helvetica,
	Catalogue,
	Chalk,
	Gothica,
	Ledger,
	Lino,
	Turri,
	Redemption,
	Gamertag,
	DreamerScript,
};

#endif