#include "pch.h"
#include "setupHooksAndNops.h"
#include "mainHackLoop.h"
#include "oneHit.h"
#include "harvest.h"
#include "globals.h"

//declare all hooks and nops
Hook mainHackLoopTramp;
Hook OneHitElimAndGodModeDetour;
Nop infAmmoNOP;
Hook harvestDataTramp;

void SetupHooksAndNops() {
	//make temporary hooks that will feed  their information into the blank declarations of our global hooks
	//main hack loop hook
	BYTE* mainHackLoopHookDst = gModuleBaseOpenGl + 0x4797E;
	Hook mainHackLoopTrampTemp(mainHackLoopHookDst, (BYTE*)MainHackLoop, 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	//infinite ammo Nop
	BYTE* infAmmoNopDst = gModuleBaseAssaultCube + 0x637E9;
	Nop infAmmoNopTemp(infAmmoNopDst, 2);
	infAmmoNOP = infAmmoNopTemp;

	//one hit detour
	BYTE* oneHitDetourDst = gModuleBaseAssaultCube + 0x29D1F;
	Hook oneHitDetourTemp(oneHitDetourDst, (BYTE*)OneHit, 5);
	OneHitElimAndGodModeDetour = oneHitDetourTemp;

	BYTE* harvestDataTrampDst = gModuleBaseAssaultCube + 0x5BDDE;
	Hook harvestDataTrampTemp(harvestDataTrampDst, (BYTE*)HarvestData, 6);
	harvestDataTramp = harvestDataTrampTemp;
}