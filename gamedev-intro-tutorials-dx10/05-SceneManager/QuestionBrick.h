#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ID_ANI_QUESTION_BRICK 50000
#define ID_ANI_QUESTION_BRICK_BROKEN 51000

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define QBRICK_STATE_BROKEN 100
#define QBRICK_STATE_SEAL 200
class CQuestionBrick : public CGameObject {
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) { EntityTag = Tag::block; SetState(QBRICK_STATE_SEAL); }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};