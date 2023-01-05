#include "CBitmap.h"

CBitmap::CBitmap()
{

}

CBitmap::~CBitmap()
{

}

void CBitmap::Render(ID2D1HwndRenderTarget* _renderTarget, int _xpos, int _ypos, int _width, int _height)
{
	_renderTarget->DrawBitmap(m_pBitmap, D2D1::RectF(_xpos, _ypos, _xpos + _width, _ypos + _height), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, m_size.width, m_size.height));
}
