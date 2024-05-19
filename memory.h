#pragma once

struct Hook {
	//get to our hook
	BYTE* hookPosition{ nullptr };
	//store stolen bytes
	BYTE stolenBytes[20]{ 0 };
	int lengthOfHook;
	//is hook active
	bool bActive = false;

	//tramp hook setup
	BYTE* desiredFunction{ nullptr };
	DWORD hookToTrampJump; //jump at the hook to the trampoline
	DWORD trampToFuncCall; //call our function from the trampoline
	DWORD returnJump; //jump at the end of trampoline back to the flow of execution
	//trampoline placement
	BYTE* trampoline{ nullptr };
	//don't corrupt stack
	BYTE preserveStack[2]{ 0x60, 0x9C }; //pushad, pushfd
	BYTE releaseStack[2]{ 0x9D, 0x61 };
	bool bTrampBuilt = false;

	//detour hook setup
	DWORD hookToDetourJump;
	DWORD returnJumpDetour;

	//functionality
	void ToggleTrampSBF();
	void ToggleTrampSBL();
	void ToggleDetour();

	//constructors
	Hook(BYTE* hookPosition, BYTE* desireFunction, int lengthOfHook);
	Hook();
};

struct Nop {
	//where at and for how long?
	BYTE* nopPositon{ nullptr };
	int length{ 0 };
	//save for toggling off
	BYTE stolenBytes[30]{ 0 };
	//used by function to know whether to store original bytes, NOP, or replace nopPosition with stolenBytes
	bool bActive = false;
	//fucntionality
	void ToggleNop();
	//constructor
	Nop(BYTE* nopPosition, int length);
	Nop();
};