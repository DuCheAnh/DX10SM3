#pragma once
#include "GameObject.h"


#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 32

#define ID_ANI_PLANT_MOVE 32000

class CPlant : public CGameObject
{
protected:

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CPlant(float x, float y);
	virtual void SetState(int state);
};