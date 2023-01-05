#include "CTile.h"
#include "CBitmap.h"

CTile::CTile(int _y, int _x)
{
	m_xBoxPos = _x;
	m_yBoxPos = _y;
	SetBitmap(L"tile6.png");
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

void CTile::Render(ID2D1HwndRenderTarget* _renderTarget)
{
	m_bitmap->Render(_renderTarget, m_xBoxPos * 100, m_yBoxPos * 100, 100, 100);
}
