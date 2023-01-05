#pragma once

#include <Windows.h>
#include <d2d1.h>

class CBitmap;

class CObj
{
protected:
	// Ä­ ÁÂÇ¥
	int m_xBoxPos = 0, m_yBoxPos = 0;
	// ÇÈ¼¿ ÁÂÇ¥
	int m_xpos, m_ypos;
	CBitmap* m_bitmap;
	D2D1_SIZE_F		m_size;
	float mag = 1.0f;
	// CAnimation

public:
	CObj();
	~CObj();
	virtual void Input();
	virtual void Update();
	virtual void Render(ID2D1HwndRenderTarget* _renderTarget);

	void SetBitmap(PCWSTR _fileName);
};

