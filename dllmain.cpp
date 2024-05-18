// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <iostream>
#include "mainHackLoop.h"
#include "setupHooksAndNops.h"
#include "consoleAndInput.h"

DWORD WINAPI HackThread(HMODULE hModule) {
    //Create Console
    FILE* f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);

    //setup our hooks and nops
    SetupHooksAndNops();

    //toggle the hooks we want
    mainHackLoopTramp.ToggleTrampSBL();

    PrintConsole();

    while (!bBreakHackThreadWhileLoop) {

    }

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

