#include "pch.h"
#include "consoleAndInput.h"
#include <iostream>
#include "setupHooksAndNops.h"

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
}

void PrintConsole() {
    system("CLS");
    std::cout << "Press NUMPAD0 for infinite ammo\n";
    std::cout << "Press NUMPAD1 for one hit eliminations and Godmode team\n";
    std::cout << "Press END to uninject\n";
    std::cout << "===========================================================\n";
    std::cout << "Inf ammo: " << (infAmmoNOP.bActive) << "\n";
    std::cout << "One hit elims and god mode: " << (OneHitElimAndGodModeDetour.bActive) << "\n";
}

void BreakHackLoop() {
    if (infAmmoNOP.bActive) infAmmoNOP.ToggleNop();
    if (OneHitElimAndGodModeDetour.bActive) OneHitElimAndGodModeDetour.ToggleDetour();

	mainHackLoopTramp.ToggleTrampSBF();
	bBreakHackThreadWhileLoop = true;
}

void ToggleConsole() {

}
