#pragma once

#include "CObj.h"
#include <d2d1.h>
#include <queue>

enum class DIR
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class CPlayer
	: public CObj
{
	bool m_isMoving = false;
	DIR m_dir;
	int m_speed = 10;

	//std::queue<DIR> m_keyQueue;

public:
	CPlayer();
	~CPlayer();

	void Input();
	void Update();
	void Render(ID2D1HwndRenderTarget* _renderTarget);
	bool CanGo(DIR _dir);
};

