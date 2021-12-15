#include "Plant.h"
#include "debug.h"
CPlant::CPlant(float x, float y) :CGameObject(x, y)
{
	EntityTag = Tag::enemy;
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_BBOX_WIDTH / 2;
	top = y - PLANT_BBOX_HEIGHT / 2;
	right = left + PLANT_BBOX_WIDTH;
	bottom = top + PLANT_BBOX_HEIGHT;
}



void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlant::Render()
{
	int aniId = ID_ANI_PLANT_MOVE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlant::SetState(int state)
{

}
