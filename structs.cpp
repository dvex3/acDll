#include "pch.h"
#include "structs.h"
#include "globals.h"
#include <cmath>

Entity entity[32];
Entity myself;
Offsets offsets;

void UpdateEntInfo() {
	for (int i = 1; i < gNumberOfPlayers; i++) {
		//distance from me? (for aimbots/esp)
		entity[i].relativeX = (*entity[i].xHeadCoord - *myself.xHeadCoord);
		entity[i].relativeY = (*entity[i].yHeadCoord - *myself.yHeadCoord);
		entity[i].relativeZ = (*entity[i].zHeadCoord - *myself.zHeadCoord);
		entity[i].distanceFromMe = sqrt((entity[i].relativeX * entity[i].relativeX) + (entity[i].relativeY * entity[i].relativeY));
	}
}