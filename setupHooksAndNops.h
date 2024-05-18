#pragma once
#include "memory.h"

extern Hook mainHackLoopTramp;
extern Hook OneHitElimAndGodModeDetour;
extern Nop infAmmoNOP;

void SetupHooksAndNops();