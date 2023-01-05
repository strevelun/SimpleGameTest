#pragma once

#include <d2d1.h>

class CBitmap
{
	ID2D1Bitmap* m_pBitmap = nullptr;
	D2D1_SIZE_F m_size = {};

public:
	CBitmap();
	~CBitmap();

	ID2D1Bitmap* GetBitmap() { return m_pBitmap; }
	void SetBitmap(ID2D1Bitmap* _bitmap) { m_pBitmap = _bitmap; m_size = _bitmap->GetSize(); }

	void Render(ID2D1HwndRenderTarget* _renderTarget, int _xpos, int _ypos, int _width, int _height);
};

