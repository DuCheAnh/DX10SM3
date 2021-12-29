#include "Koopa.h"
#include "debug.h"
CKoopa::CKoopa(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	shot = false;
	SetState(KOOPA_STATE_WALKING);
	EntityTag = Tag::Enemy;
}

void CKoopa::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_MOVING)
	{
		left = x - KOOPA_BBOX_WIDTH/2;
		top = y - KOOPA_BBOX_WIDTH /2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_WIDTH;
	}
	else
	{ 
		left = x - KOOPA_BBOX_WIDTH/2;
		top = y - KOOPA_BBOX_HEIGHT/2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CKoopa*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING;
	if (state == KOOPA_STATE_DIE) 
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	else if (state == KOOPA_STATE_SHOT)
	{
		aniId = ID_ANI_KOOPA_SHOT;
	}
	else if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING)
	{
		aniId = ID_ANI_KOOPA_SHELL_MOVING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case KOOPA_STATE_DIE:
			die_start = GetTickCount64();
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case KOOPA_STATE_SHOT:
			die_start = GetTickCount64();
			vx = 0;
			ay = 0.0015f;
			vy = 0;
			break;
		case KOOPA_STATE_WALKING: 
			vx = -KOOPA_WALKING_SPEED;
			break;
		case KOOPA_STATE_SHELL:
			vx= 0;
			break;	
		case KOOPA_STATE_SHELL_MOVING:
			vx= KOOPA_SHELL_SPEED*kick_dir;
			break;
	}
}

void CKoopa::GotKick(float dir)
{
	kick_dir = dir;
	SetState(KOOPA_STATE_SHELL_MOVING);
}