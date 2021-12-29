#pragma once
#include "GameObject.h"

#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 32

#define ID_ANI_PLANT_UP_LLEFT 32000
#define ID_ANI_PLANT_UP_LRIGHT 32100
#define ID_ANI_PLANT_DOWN_LLEFT 32200
#define ID_ANI_PLANT_DOWN_LRIGHT 32300

#define PLANT_STATE_MOVING_UP 100
#define PLANT_STATE_MOVING_DOWN 200
#define PLANT_STATE_SHOOTING 300
#define PLANT_STATE_WAITING 400

#define WAITING_WAIT_TIME 5000
#define SHOOT_WAIT_TIME 3000

#define PLANT_MOVING_DISTANCE 32
#define PLANT_MOVING_SPEED 0.02
class CPlant : public CGameObject
{
protected:
	ULONGLONG timer_start;
	float distance;
	int direction = -1;
	bool shot = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CPlant(float x, float y);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
	void Destroy() { this->isDeleted = true; }
};