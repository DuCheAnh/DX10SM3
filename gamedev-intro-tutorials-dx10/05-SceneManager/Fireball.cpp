#include <algorithm>
#include "debug.h"

#include "Fireball.h"
#include "Game.h"
#include "Collision.h"

#include "Plant.h"

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx = FIREBALL_SPEED;
	if (bounces < 1) isDeleted = true;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireball::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (e->nx != 0)
	{
		bounces = 0;
	}
	else if (e->ny < 0)
	{
		vy = -FIREBALL_DEFLECT_FORCE;
		bounces -= 1;
	}
	
}

void CFireball::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);
	this->isDeleted = true;
	plant->Destroy();
}



void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);

	RenderBoundingBox();


}


void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - FIREBALL_BBOX_HEIGHT / 2;
		top = y - FIREBALL_BBOX_WIDTH / 2;
		right = left + FIREBALL_BBOX_HEIGHT;
		bottom = top + FIREBALL_BBOX_WIDTH;
}

