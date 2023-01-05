#include "CObj.h"
#include "CBitmap.h"
#include "Util.h"

CObj::CObj()
{
	m_bitmap = new CBitmap();
}

CObj::~CObj()
{
}

void CObj::Input()
{
}

void CObj::Update()
{
}

void CObj::Render(ID2D1HwndRenderTarget* _renderTarget)
{
	
}

void CObj::SetBitmap(PCWSTR _fileName)
{
	ID2D1Bitmap* temp = m_bitmap->GetBitmap();
	LoadBitmapFromFile(_fileName, &temp);
	m_bitmap->SetBitmap(temp);
}
