#include "pch.h"
#include "oneHit.h"
#include "setupHooksAndNops.h"

#define teamOffset 0x238
#define playerNumber 0xF0
#define healthOffset 0x04
#define armorOffset 0x08
#define maxhealth 0x64
#define maxArmor 0x64
#define eliminate 0

int myTeam = 5;

void __declspec(naked)OneHit() {
	//someone send help
	__asm {
		mov eax, edi

		push ecx
		cmp [ebx + playerNumber], 0
		jne continue
		mov ecx, [ebx + teamOffset]
		mov [myTeam], ecx
		jmp end

		continue:
		mov ecx, [myTeam]
		cmp [ebx + teamOffset], ecx
		je end
		sub [ebx + healthOffset], maxhealth

		end:
		pop ecx
		jmp OneHitElimAndGodModeDetour.returnJumpDetour
	}
}