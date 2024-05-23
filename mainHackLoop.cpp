#include "pch.h"
#include "mainHackLoop.h"
#include "setupHooksAndNops.h"	
#include "consoleAndInput.h"
#include "globals.h"
#include "structs.h"
#include "harvest.h"
#include "aimbot.h"
#include "esp.h"

#define numberOfPlayers (gModuleBaseAssaultCube + 0x10F500)

void MainHackLoop() {
	//has anyone joined/left the game?
	//if so, set the corect new number of playeres, then toggle the harvesting again if it isn't already on
	int currentNumberOfPlayers = *(int*)(numberOfPlayers);
	if (gNumberOfPlayers != currentNumberOfPlayers) {
		gNumberOfPlayers = currentNumberOfPlayers;
		if (!harvestDataTramp.bActive) harvestDataTramp.ToggleTrampSBF();
	}

	//is our harvesting hook finished?
	if (harvestDataTramp.bActive) return;

	UpdateEntInfo();

	if (bAimbotStatus) Aimbot(ClosestEnemy());

	DrawEverything();

	GetInput();
}