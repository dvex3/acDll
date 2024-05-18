#pragma once
#include "memory.h"

extern Hook mainHackLoopTramp;
extern Hook infAmmoDetour;
// extern Hook oneHitTramp;
extern Hook oneHitDetour;
extern Nop infAmmoNOP;

void SetupHooksAndNops();