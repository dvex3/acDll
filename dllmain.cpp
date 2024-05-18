// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <iostream>
#include "mainHackLoop.h"
#include "setupHooksAndNops.h"

DWORD WINAPI HackThread(HMODULE hModule) {
    //Create Console
    FILE* f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);

    //setup our hooks and nops
    SetupHooksAndNops();

    //toggle the hooks we want
    mainHackLoopTramp.ToggleTrampSBL();

    std::cout << "Press NUMPAD0 for infAmmoDetour\n";
    std::cout << "Press NUMPAD1 for infAmmoNOP\n";
    std::cout << "Press NUMPAD2 for oneHitDetour\n";
    // std::cout << "Press NUMPAD3 for oneHitTramp\n";
    std::cout << "Press END to uninject\n";

    while (!bBreakHackThreadWhileLoop) {

    }

    if (infAmmoDetour.bActive) infAmmoDetour.ToggleDetour();
    if (infAmmoNOP.bActive) infAmmoNOP.ToggleNop();
    if (oneHitDetour.bActive) oneHitDetour.ToggleDetour();
    // if (oneHitTramp.bActive) oneHitTramp.ToggleTrampSBF();

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

