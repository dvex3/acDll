#include "pch.h"
#include "aimbot.h"
#include "globals.h"
#include <cmath>

#define FindTargetOffset 0x8ABD0

bool bAimbotStatus = false;

Entity* ClosestEnemy() {
	Entity* closestEnemy = 0; //storing the element of the closest enemy, if stays at 0 (aimbot will purposefully not work)
	float closestDistance = 99999.0f;

	//find closest enemy, starts on 1 to avoid me(I'm 0)
	for (int i = 1; i < gNumberOfPlayers; i++) {
		//if not dead or teammate, and if closer, return your element for aimbot
		if ((!(*entity[i].bDead)) && (*entity[i].team != *myself.team) && (entity[i].distanceFromMe < closestDistance) && (entity[i].bTargetable)) {
			closestDistance = entity[i].distanceFromMe;
			closestEnemy = &entity[i];
		}
	}

	return closestEnemy;
}

void Aimbot(Entity* lockOnTarget) {
	if (!lockOnTarget) return; //if lockOnTarget is 0, don't process aimbot

	//calculating angles
	float tempYaw = atan2(entity[*lockOnTarget->playerNumber].relativeY, entity[*lockOnTarget->playerNumber].relativeX); //answer is given in radians
	tempYaw = (tempYaw * 180 / gPI) + 90; //have to add 90 because of misallignment in game
	float tempPitch = atan2(entity[*lockOnTarget->playerNumber].relativeZ, entity[*lockOnTarget->playerNumber].distanceFromMe);
	tempPitch *= (180 / gPI);

	*myself.yaw = tempYaw;
	*myself.pitch = tempPitch;
}

bool BeTargetable(Entity& target, Entity& myself) {
	bool bTargetable = 0;

	void* FindTarget = (void*)(gModuleBaseAssaultCube + FindTargetOffset);

	float toZ = *myself.zHeadCoord;
	float toY = *myself.yHeadCoord;
	float toX = *myself.xHeadCoord;
	float fromZ = *target.zHeadCoord;
	float fromY = *target.yHeadCoord;
	float fromX = *target.xHeadCoord;

	__asm {
		//push arguments onto stack (cdecl pushes right to left)
		push toZ
		push toY
		push toX
		push fromZ
		push fromY
		push fromX

		//only eax has to be manipulated in this case to work properly
		mov eax, 0
		mov cl, 0

		call FindTarget

		//because the function we called has a cdecl calling convention, the answer will be returned in eax, so we grab the answer then cleant eh stack because the caller has to do that with cdecl functions
		mov [bTargetable], al
		add esp, 0x18
	}

	return bTargetable;
}