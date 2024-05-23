#pragma once
#include "structs.h"

void SetupGL();
void DrawEverything();
void DrawBox(Entity& entity);
bool WorldToScreen(Entity& entity);

extern int viewport[4];
extern bool bEspStatus;
