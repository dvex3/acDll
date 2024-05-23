#pragma once
#include "structs.h"

Entity* ClosestEnemy();

void Aimbot(Entity* lockOnTarget);

extern bool bAimbotStatus;

bool BeTargetable(Entity& target, Entity& myself);