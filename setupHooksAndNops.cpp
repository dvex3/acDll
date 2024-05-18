#include "pch.h"
#include "setupHooksAndNops.h"
#include "mainHackLoop.h"
#include "infAmmo.h"
#include "oneHit.h"

//declare all hooks and nops
Hook mainHackLoopTramp;
Hook infAmmoDetour;
// Hook oneHitTramp;
Hook oneHitDetour;
Nop infAmmoNOP;

void SetupHooksAndNops() {
	//make sure we have our module bases
	BYTE* moduleBaseAssaultCube = (BYTE*)GetModuleHandle(L"ac_client.exe");
	BYTE* moduleBaseOpenGl = (BYTE*)GetModuleHandle(L"opengl32.dll");

	//make temporary hooks that will feed  their information into the blank declarations of our global hooks
	//main hack loop hook
	BYTE* mainHackLoopHookDst = moduleBaseOpenGl + 0x47ADE;
	Hook mainHackLoopTrampTemp(mainHackLoopHookDst, (BYTE*)MainHackLoop, 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	//infinite ammo detour
	BYTE* infAmmoDetourDst = moduleBaseAssaultCube + 0x637E6;
	Hook infAmmoDetourTemp(infAmmoDetourDst, (BYTE*)InfAmmo, 5);
	infAmmoDetour = infAmmoDetourTemp;

	//infinite ammo Nop
	BYTE* infAmmoNopDst = moduleBaseAssaultCube + 0x637E9;
	Nop infAmmoNopTemp(infAmmoNopDst, 2);
	infAmmoNOP = infAmmoNopTemp;

	//one hit detour
	BYTE* oneHitDetourDst = moduleBaseAssaultCube + 0x29D1F;
	Hook oneHitDetourTemp(oneHitDetourDst, (BYTE*)oneHit, 5);
	oneHitDetour = oneHitDetourTemp;

	//one hit trmap
	/*
	BYTE* oneHitTrampDst = moduleBaseAssaultCube + 0x29D1F;
	Hook oneHitTrampTemp(oneHitTrampDst, (BYTE*)oneHit, 5);
	oneHitTramp = oneHitTrampTemp;
	*/
}