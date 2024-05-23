#include "pch.h"
#include "esp.h"
#include "globals.h"

#define everyoneButMe 1
#define screenWidth viewport[2]
#define screenHeight viewport[3]

int viewport[4]{ 0 };
bool bEspStatus = false;

void SetupGL() {
	//get the height and width of the screen
	glGetIntegerv(GL_VIEWPORT, viewport);

	//tell openGL we are about to do Projection math orthogonally
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
}

bool WorldToScreen(Entity& entity) {
	static float* MVPmatrix = (float*)(gModuleBaseAssaultCube + 0x101AE8);

	//get clip values
	Vector4 clip;
	clip.x = *entity.xHeadCoord * MVPmatrix[0] + *entity.yHeadCoord * MVPmatrix[4] + *entity.zHeadCoord * MVPmatrix[8] + MVPmatrix[12];
	clip.y = *entity.xHeadCoord * MVPmatrix[1] + *entity.yHeadCoord * MVPmatrix[5] + *entity.zHeadCoord * MVPmatrix[9] + MVPmatrix[13];
	clip.z = *entity.xHeadCoord * MVPmatrix[2] + *entity.yHeadCoord * MVPmatrix[6] + *entity.zHeadCoord * MVPmatrix[10] + MVPmatrix[14];
	clip.w = *entity.xHeadCoord * MVPmatrix[3] + *entity.yHeadCoord * MVPmatrix[7] + *entity.zHeadCoord * MVPmatrix[11] + MVPmatrix[15];

	//if behind the camera, don't update information
	if (clip.w < 0.1f) return false;

	//normalize the clip values by dividing by w (perspective division) (this gives us a value from -1 to 1 to represent on our screen, but it's not pixel info yet)
	Vector4 NDC;
	NDC.x = clip.x / clip.w;
	NDC.y = clip.y / clip.w;
	NDC.z = clip.z / clip.w;

	//turn the normalized coordinates into pixel data
	entity.screenX = (screenWidth / 2 * NDC.x) + (NDC.x + screenWidth / 2);
	entity.screenY = (screenWidth / 2 * NDC.y) + (NDC.y + screenWidth / 2);

	return true;
}

void DrawEverything() {
	//mkae sure openGL is ready to draw with up to date information
	SetupGL();

	//loop through every alive/visible entity and draw boxes around them
	if (bEspStatus) {
		for (int i = everyoneButMe; i < gNumberOfPlayers; i++) {
			if (!*entity[i].bDead && entity[i].bVisible)
				DrawBox(entity[i]);
		}
	}
}

void DrawBox(Entity& entity) {
	//set color. red enemies, green team
	if (*entity.team != *myself.team) glColor3ub(color.red[0], color.red[1], color.red[2]);
	else glColor3ub(color.green[0], color.green[1], color.green[2]);

	//adjusted distance
	static float gameUnits = 450.0f;
	float distanceAdjustment = gameUnits / entity.distanceFromMe;

	//draw a box with 2.0f sized lines
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(entity.screenX - distanceAdjustment, entity.screenY + distanceAdjustment);
	glVertex2f(entity.screenX + distanceAdjustment, entity.screenY + distanceAdjustment);
	glVertex2f(entity.screenX + distanceAdjustment, entity.screenY - distanceAdjustment);
	glVertex2f(entity.screenX - distanceAdjustment, entity.screenY - distanceAdjustment);
	glEnd();
}