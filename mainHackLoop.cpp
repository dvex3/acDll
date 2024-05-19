#include "pch.h"
#include "mainHackLoop.h"
#include "setupHooksAndNops.h"	
#include "consoleAndInput.h"
#include "globals.h"
#include "structs.h"

#define numberOfPlayers (gModuleBaseAssaultCube + 0x10F500)

void MainHackLoop() {
	//has anyone joined/left the game?
	//if so, set the corect new number of playeres, then toggle the harvesting again if it isn't already on
	int currentNumberOfPlayers = *(int*)(numberOfPlayers);
	if (gNumberOfPlayers != currentNumberOfPlayers) {
		gNumberOfPlayers = currentNumberOfPlayers;
		if (!harvestDataTramp.bActive)
			harvestDataTramp.ToggleTrampSBF();
	}

	//is our harvesting hook finished?
	if (harvestDataTramp.bActive) return;

	//harvesting is finished, we can now dereference without crashing the game and use all our functionality
	/*
	*myself.arAmmo = 999;
	for (int i = 0; i < gNumberOfPlayers; i++) {
		if (*entity[i].team != *myself.team)
			*entity[i].health = 1;
	}
	*/
	
	//hitbox only, viewmodel not included
	for (int i = 1; i < gNumberOfPlayers; i++) {
		if (*(entity[i].team) != *(entity[0].team)) {
			*(entity[i].health) = 0x1;
			*(entity[i].xCoord) = *(entity[0].xCoord) + 0x5;
			*(entity[i].yCoord) = *(entity[0].yCoord) + 0x5;
			*(entity[i].zCoord) = *(entity[0].zCoord);
		}
	}

	GetInput();
}