#pragma once
#include <Windows.h>
#include <cstdint>

struct Entity {
	//pointers gotten from game
	BYTE* playerBase = nullptr;
	BYTE* bDead = nullptr;
	float* xHeadCoord = nullptr;
	float* yHeadCoord = nullptr;
	float* zHeadCoord = nullptr;
	int* team = nullptr;
	int* playerNumber = nullptr;
	int* health = nullptr;
	char* name = nullptr;
	float* xOrigin = nullptr;
	float* yOrigin = nullptr;
	float* zOrigin = nullptr;

	//DLL only vars, used for checks and aimbot/ESP math
	bool bChecked = false;
	float relativeX = NULL;
	float relativeY = NULL;
	float relativeZ = NULL;
	float distanceFromMe = 99999.0f;

	//just for me
	float* yaw = nullptr;
	float* pitch = nullptr;
	int* arAmmo = nullptr;
};

struct Offsets {
	DWORD xHeadCoord = 0x04;
	DWORD yHeadCoord = 0x08;
	DWORD zHeadCoord = 0x0C;
	DWORD team = 0x32C;
	DWORD playerNumber = 0x1E4;
	DWORD bDead = 0x82;
	DWORD name = 0x225;
	DWORD health = 0xF8;

	//just for me
	DWORD yaw = 0x40;
	DWORD pitch = 0x44;
	DWORD arAmmo = 0x150;
};

class Ent
{
public:
	char pad_0000[4]; //0x0000
	float xHeadCoord; //0x0004
	float yHeadCoord; //0x0008
	float zHeadCoord; //0x000C
	char pad_0010[36]; //0x0010
	float originX; //0x0034
	float originY; //0x0038
	float originZ; //0x003C
	float yaw; //0x0040
	float pitch; //0x0044
	char pad_0048[58]; //0x0048
	bool bDead; //0x0082
	char pad_0083[117]; //0x0083
	int32_t health; //0x00F8
	char pad_00FC[84]; //0x00FC
	int32_t arAmmo; //0x0150
	char pad_0154[144]; //0x0154
	int32_t playerNumber; //0x01E4
	char pad_01E8[61]; //0x01E8
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t team; //0x032C
}; //Size: 0x0330

extern Entity entity[32];
extern Entity myself;
extern Offsets offsets;

void UpdateEntInfo();
