#include "pch.h"
#include "memory.h"

//reach inside hook struct to access our hook constructor and define that function
Hook::Hook(BYTE* hookPosition, BYTE* desireFunction, int lengthOfHook) {
	this->hookPosition = hookPosition;
	this->desiredFunction = desireFunction;
	if (lengthOfHook < 5)
		this->lengthOfHook = 5;
	else
		this->lengthOfHook = lengthOfHook;

	//copy stolen bytes
	memcpy(stolenBytes, hookPosition, lengthOfHook);

	//allocate room for our trampoline
	trampoline = (BYTE*)VirtualAlloc(nullptr, 30, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//setup tramp jumps
	hookToTrampJump = (DWORD)(trampoline - hookPosition) - 5;
	returnJump = (DWORD)(hookPosition + lengthOfHook) - (DWORD)(trampoline + lengthOfHook + sizeof(preserveStack) + 5 + sizeof(releaseStack)) - 5;

	//setup detour jumps
	hookToDetourJump = (DWORD)(desireFunction - hookPosition) - 5;
	returnJumpDetour = (DWORD)(hookPosition + lengthOfHook);
}

Hook::Hook() {

}

void Hook::ToggleTrampSBF() {
	//toggle hook
	bActive = !bActive;

	if (bActive) {
		//making it so that we can execute/read/write bytes at hook location
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);

		//is the trampoline already built? if so, skip making the trampoline
		if (!bTrampBuilt) {
			//in our trampoline, jump to our space in the DLL for the specified function
			trampToFuncCall = (DWORD)desiredFunction - (DWORD)(trampoline + lengthOfHook + sizeof(preserveStack)) - 5;

			//stolen byte placed, stack preserved, call our desired function
			memcpy(trampoline, (void*)hookPosition, lengthOfHook);
			memcpy(trampoline + lengthOfHook, preserveStack, sizeof(preserveStack));
			memset(trampoline + lengthOfHook + sizeof(preserveStack), 0xE8, 1);
			*(DWORD*)(trampoline + lengthOfHook + sizeof(preserveStack) + 1) = trampToFuncCall;

			//release stack, jump back to after hook
			memcpy(trampoline + lengthOfHook + sizeof(preserveStack) + 5, releaseStack, sizeof(releaseStack));
			memset(trampoline + lengthOfHook + sizeof(preserveStack) + 5 + sizeof(releaseStack), 0xE9, 1);
			*(DWORD*)(trampoline + lengthOfHook + sizeof(preserveStack) + 5 + sizeof(releaseStack) + 1) = returnJump;

			//trampoline is built
			bTrampBuilt = true;
		}

		//set hook inside game's memory
		memset(hookPosition, 0x90, lengthOfHook);
		*(BYTE*)hookPosition = 0xE9;
		*(DWORD*)(hookPosition + 1) = hookToTrampJump;

		//restore protection
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, &oldProtection);
	}

	else {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(hookPosition, stolenBytes, lengthOfHook);
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}
}

void Hook::ToggleTrampSBL() {
	bActive = !bActive;

	if (bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);

		if (!bTrampBuilt) {
			trampToFuncCall = (DWORD)desiredFunction - (DWORD)(trampoline + sizeof(preserveStack)) - 5;

			memcpy(trampoline, preserveStack, sizeof(preserveStack));
			memset(trampoline + sizeof(preserveStack), 0xE8, 1);
			*(DWORD*)(trampoline + sizeof(preserveStack) + 1) = trampToFuncCall;

			memcpy(trampoline + sizeof(preserveStack) + 5, releaseStack, sizeof(releaseStack));
			memcpy(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack), (void*)hookPosition, lengthOfHook);
			memset(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack) + lengthOfHook, 0xE9, 1);
			*(DWORD*)(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack) + lengthOfHook + 1) = returnJump;

			bTrampBuilt = true;
		}

		memset(hookPosition, 0x90, lengthOfHook);
		*(BYTE*)hookPosition = 0xE9;
		*(DWORD*)(hookPosition + 1) = hookToTrampJump;

		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}

	else {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(hookPosition, stolenBytes, lengthOfHook);
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, &oldProtection);
	}
}

void Hook::ToggleDetour() {
	//toggle hook
	bActive = !bActive;

	if (bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);

		//set detour hook inside game's memory, the detour jumps back for us
		memset(hookPosition, 0x90, lengthOfHook);
		*(BYTE*)hookPosition = 0xE9;
		*(DWORD*)(hookPosition + 1) = hookToDetourJump;

		//restore protections
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}

	else {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(hookPosition, stolenBytes, lengthOfHook);
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, &oldProtection);
	}
}



Nop::Nop(BYTE* nopPosition, int length) {
	this->nopPositon = nopPosition;
	this->length = length;
	memcpy(stolenBytes, nopPosition, length);
}

Nop::Nop() {

}

void Nop::ToggleNop() {
	//toggle NOP
	bActive = !bActive;

	if (bActive) {
		DWORD oldProtecion;
		VirtualProtect(nopPositon, length, PAGE_EXECUTE_READWRITE, &oldProtecion);
		memset(nopPositon, 0x90, length);
		VirtualProtect(nopPositon, length, oldProtecion, &oldProtecion);
	}

	else {
		DWORD oldProtecion;
		VirtualProtect(nopPositon, length, PAGE_EXECUTE_READWRITE, &oldProtecion);
		memcpy(nopPositon, stolenBytes, length);
		VirtualProtect(nopPositon, length, oldProtecion, &oldProtecion);
	}
}