#include "pch.h"
#include "setupHooksAndNops.h"
#include "mainHackLoop.h"
#include "oneHit.h"

//declare all hooks and nops
Hook mainHackLoopTramp;
Hook OneHitElimAndGodModeDetour;
Nop infAmmoNOP;

void SetupHooksAndNops() {
	//make sure we have our module bases
	BYTE* moduleBaseAssaultCube = (BYTE*)GetModuleHandle(L"ac_client.exe");
	BYTE* moduleBaseOpenGl = (BYTE*)GetModuleHandle(L"opengl32.dll");

	//make temporary hooks that will feed  their information into the blank declarations of our global hooks
	//main hack loop hook
	BYTE* mainHackLoopHookDst = moduleBaseOpenGl + 0x4797E;
	Hook mainHackLoopTrampTemp(mainHackLoopHookDst, (BYTE*)MainHackLoop, 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	//infinite ammo Nop
	BYTE* infAmmoNopDst = moduleBaseAssaultCube + 0x637E9;
	Nop infAmmoNopTemp(infAmmoNopDst, 2);
	infAmmoNOP = infAmmoNopTemp;

	//one hit detour
	BYTE* oneHitDetourDst = moduleBaseAssaultCube + 0x29D1F;
	Hook oneHitDetourTemp(oneHitDetourDst, (BYTE*)oneHit, 5);
	OneHitElimAndGodModeDetour = oneHitDetourTemp;
}