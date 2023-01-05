#pragma once

#include "CObj.h"

class CTile
	: public CObj
{
	//int m_size = 100;

public:
	CTile(int _y, int _x);
	~CTile();

	void Input();
	void Update();
	void Render(ID2D1HwndRenderTarget* _renderTarget);
};

