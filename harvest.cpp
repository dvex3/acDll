#include "pch.h"
#include "harvest.h"
#include "structs.h"
#include "setupHooksAndNops.h"
#include "globals.h"

void HarvestData() {
	int* currentPlayerNumber;
	BYTE* playerBase;
	__asm {
		push ebx

		lea ebx, [esi] //playerBaseAddress
		mov playerBase, ebx
		lea ebx, [esi + 0x1E4] //playerNumber
		mov currentPlayerNumber, ebx

		pop ebx
	}

	MoveDataIntoEnt(playerBase, currentPlayerNumber);

	//is everyone checked?
	for (int i = 0; i < gNumberOfPlayers; i++) {
		if (!entity[i].bChecked)
			return;
	}

	//if everyone is checked, setup for next possible check, toggleHarvesting
	for (int i = 0; i < gNumberOfPlayers; i++) {
		entity[i].bChecked = false;
	}

	//disable hook
	harvestDataTramp.ToggleTrampSBF();
}

void MoveDataIntoEnt(BYTE* playerBase, int* playerNumber) {
	//assign addressed to specified global Entity[]
	entity[*playerNumber].playerBase = playerBase;
	entity[*playerNumber].bDead = (playerBase + offsets.bDead);
	entity[*playerNumber].playerNumber = (int*)(playerBase + offsets.playerNumber);
	entity[*playerNumber].team = (int*)(playerBase + offsets.team);
	entity[*playerNumber].health = (int*)(playerBase + offsets.health);
	entity[*playerNumber].xHeadCoord = (float*)(playerBase + offsets.xHeadCoord);
	entity[*playerNumber].yHeadCoord = (float*)(playerBase + offsets.yHeadCoord);
	entity[*playerNumber].zHeadCoord = (float*)(playerBase + offsets.zHeadCoord);
	entity[*playerNumber].name = (char*)(playerBase + offsets.name);
	entity[*playerNumber].bChecked = true;

	//im playerNumber 0
	if (*playerNumber == 0) {
		myself = entity[0];
		myself.pitch = (float*)(playerBase + offsets.pitch);
		myself.yaw = (float*)(playerBase + offsets.yaw);
		myself.arAmmo = (int*)(playerBase + offsets.arAmmo);
	}
}
