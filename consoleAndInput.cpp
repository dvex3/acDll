#include "pch.h"
#include "consoleAndInput.h"
#include <iostream>
#include "setupHooksAndNops.h"
#include "aimbot.h"
#include "esp.h"

bool bBreakHackThreadWhileLoop = false;

void GetInput() {
	if (GetAsyncKeyState(VK_END) & 1) {
		BreakHackLoop();
	}

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
		infAmmoNOP.ToggleNop();
		PrintConsole();
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		OneHitElimAndGodModeDetour.ToggleDetour();
		PrintConsole();
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
		bAimbotStatus = !bAimbotStatus;
		PrintConsole();
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
		bEspStatus = !bEspStatus;
		PrintConsole();
	}
}

void PrintConsole() {
    system("CLS");
    std::cout << "Press NUMPAD0 toa activate infinite ammo\n";
    std::cout << "Press NUMPAD1 to activate one hit eliminations and Godmode team\n";
	std::cout << "Press NUMPAD2 to activate aimbot\n";
	std::cout << "Press NUMPAD3 to activate ESP\n";
    std::cout << "Press END to uninject\n";
    std::cout << "===========================================================\n";
    std::cout << "Inf ammo: " << ((infAmmoNOP.bActive) ? "ON" : "OFF") << "\n";
    std::cout << "One hit elims and god mode: " << ((OneHitElimAndGodModeDetour.bActive) ? "ON" : "OFF") << "\n";
	std::cout << "Aimbot: " << ((bAimbotStatus) ? "ON" : "OFF") << "\n";
	std::cout << "ESP: " << ((bEspStatus) ? "ON" : "OFF") << "\n";
}

void BreakHackLoop() {
	//make sure everything is deactivated
    if (infAmmoNOP.bActive) infAmmoNOP.ToggleNop();
    if (OneHitElimAndGodModeDetour.bActive) OneHitElimAndGodModeDetour.ToggleDetour();
	if (harvestDataTramp.bActive) harvestDataTramp.ToggleTrampSBF();
	if (bAimbotStatus) bAimbotStatus = false;
	if (bEspStatus) bEspStatus = false;

	//toggle off main hack loop hook, then break the while loop inside the HackThread()
	mainHackLoopTramp.ToggleTrampSBF();
	bBreakHackThreadWhileLoop = true;
}

void ToggleConsole() {
	static bool bActive = false;
	static FILE* f;
	bActive = !bActive;

	if (bActive) {
		AllocConsole();
		freopen_s(&f, "CONOUT$", "w", stdout);
	}

	else {
		fclose(f);
		FreeConsole();
	}
}
