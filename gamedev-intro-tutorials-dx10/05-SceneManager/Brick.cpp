#include "Brick.h"
#include "debug.h"
#include "Mario.h"
CBrick::CBrick(float x,float y) :CGameObject(x, y)
{
	EntityTag = Tag::block;
	break_start = -1; 
	SetState(BRICK_STATE_NORMAL);
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	RenderBoundingBox();
}
void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == BRICK_STATE_BROKEN)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CBrick::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
		case BRICK_STATE_BROKEN:
			break;
		case BRICK_STATE_NORMAL:
			break;
	}
}