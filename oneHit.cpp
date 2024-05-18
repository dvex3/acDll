#include "pch.h"
#include "oneHit.h"
#include "setupHooksAndNops.h"

void __declspec(naked)oneHit() {
	//someone send help
	__asm {
		mov eax, edi

		oneHit:
		push ecx
		cmp [ebx + 0x238], 0
		pop ecx
		je end
		sub [ebx + 0x04], 100
		jmp end

		end:
		jmp OneHitElimAndGodModeDetour.returnJumpDetour
	}
}