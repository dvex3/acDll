#include "pch.h"
#include "mainHackLoop.h"
#include "setupHooksAndNops.h"	

bool bBreakHackThreadWhileLoop = false;

void MainHackLoop() {
	if (GetAsyncKeyState(VK_END) & 1) {
		mainHackLoopTramp.ToggleTrampSBF();	
		bBreakHackThreadWhileLoop = true;
	}

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
		if (infAmmoNOP.bActive) infAmmoNOP.ToggleNop();
		infAmmoDetour.ToggleDetour();
		std::cout << "Infinite Ammo Detour: " << (infAmmoDetour.bActive) << "\n";
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		if (infAmmoDetour.bActive) infAmmoDetour.ToggleDetour();
		infAmmoNOP.ToggleNop();
		std::cout << "Infinite Ammo NOP: " << (infAmmoNOP.bActive) << "\n";
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
		oneHitDetour.ToggleDetour();
		std::cout << "One Hit Detour: " << (oneHitDetour.bActive) << "\n";
	}

	/*
	if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
		oneHitTramp.ToggleTrampSBL();
		std::cout << "One Hit Tramp: " << (oneHitTramp.bActive) << "\n";
	}
	*/
}