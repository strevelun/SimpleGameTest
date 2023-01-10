#include "CTile.h"
#include "CBitmap.h"

CTile::CTile(int _y, int _x, ObjType _type)
{
	m_type = _type;
	m_xBoxPos = _x;
	m_yBoxPos = _y;
	SetBitmap(L"Resource\\Image\\Tile\\Walkable\\tile5.png");
	m_size = m_bitmap->GetBitmap()->GetSize();
}

CTile::~CTile()
{
}

void CTile::Input()
{
}

void CTile::Update()
{
}

void CTile::Render(ID2D1HwndRenderTarget* _renderTarget, int _mag)
{
	m_bitmap->Render(_renderTarget, m_xBoxPos * _mag, m_yBoxPos * _mag, _mag, _mag);
}
