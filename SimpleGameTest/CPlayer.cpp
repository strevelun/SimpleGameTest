#include <Windows.h>

#include "CPlayer.h"
#include "Setting.h"
#include "CBitmap.h"
#include "Game.h"
#include "CScene.h"

CPlayer::CPlayer()
{

	SetBitmap(L"player.png");
	m_size = m_bitmap->GetBitmap()->GetSize();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Input()
{
	if (m_isMoving)
		return;

	if (GetAsyncKeyState(KEY_UP) & 0x8000)
	{
		m_isMoving = true;
		m_dir = DIR::UP;
		m_yBoxPos -= 1;
	}
	else if (GetAsyncKeyState(KEY_DOWN) & 0x8000)
	{
		m_isMoving = true;
		m_dir = DIR::DOWN;
		m_yBoxPos += 1;
	}
	else if (GetAsyncKeyState(KEY_LEFT) & 0x8000)
	{
		m_isMoving = true;
		m_dir = DIR::LEFT;
		m_xBoxPos -= 1;
	}
	else if (GetAsyncKeyState(KEY_RIGHT) & 0x8000)
	{
		m_isMoving = true;
		m_dir = DIR::RIGHT;
		m_xBoxPos += 1;
	}
	else
		m_dir = DIR::NONE;

}

void CPlayer::Update(int _mag)
{
	char str[20] = "";
	switch (m_dir)
	{
	case DIR::UP:
		if (!CanGo(m_dir, _mag))
			break;

		m_ypos -= m_speed;
		if ((m_yBoxPos) *100 >= m_ypos)
		{
			m_ypos = (m_yBoxPos) * 100;
			m_isMoving = false;
		}
		break;
	case DIR::DOWN:
		if (!CanGo(m_dir, _mag))
			break;

		m_ypos += m_speed;
		if (m_yBoxPos * 100 <= m_ypos)
		{
			m_ypos = m_yBoxPos * 100;
			m_isMoving = false;
		}
		break;
	case DIR::LEFT:
		if (!CanGo(m_dir, _mag))
			break;
		m_xpos -= m_speed;
		if ((m_xBoxPos) *100 >= m_xpos)
		{
			m_xpos = (m_xBoxPos) * 100;
			m_isMoving = false;
		}
		break;
	case DIR::RIGHT:
		if (!CanGo(m_dir, _mag ))
			break;

		m_xpos += m_speed;
		if (m_xBoxPos * 100 <= m_xpos)
		{
			m_xpos = m_xBoxPos * 100; // 디폴트 크기 기준으로 곱해야
			m_isMoving = false;
		}
		break;
	}
}

void CPlayer::Render(ID2D1HwndRenderTarget* _renderTarget, int _mag)
{
	float temp =  m_xpos * (_mag / 100.f);

#ifdef _DEBUG
	char str[50];
	sprintf_s(str, "%f = %d * (%d / 100.0f)\n", temp, m_xpos, _mag);
	OutputDebugStringA(str);
#endif

	m_bitmap->Render(_renderTarget, temp, m_ypos * _mag / 100.0f, _mag, _mag);
}

bool CPlayer::CanGo(DIR _dir, int _mag)
{
	switch (_dir)
	{
	case DIR::UP:
		if (m_ypos - m_speed < 0)
		{
			m_isMoving = false;
			m_yBoxPos = 0;
			m_ypos = 0;
		}
		break;
	case DIR::DOWN:
		if (m_ypos + m_speed > SCREEN_HEIGHT - _mag)
		{
			m_isMoving = false;
			m_yBoxPos = (SCREEN_HEIGHT / _mag) - 1;
			m_ypos = SCREEN_HEIGHT - _mag;
			return false;
		}
		break;
	case DIR::LEFT:
		if (m_xpos - m_speed < 0)
		{
			m_isMoving = false;
			m_xBoxPos = 0;
			m_xpos = 0;
			return false;
		}
		break;
	case DIR::RIGHT:
		if (m_xpos + m_speed > SCREEN_WIDTH - _mag)
		{
			m_isMoving = false;
			m_xBoxPos = (SCREEN_WIDTH / _mag) - 1;
			m_xpos = SCREEN_WIDTH - _mag;
			return false;
		}
		break;
	}

	CTile* tile = CScene::GetInst()->GetTileAtPos(m_xBoxPos, m_yBoxPos);
	if (tile->GetType() == ObjType::None || tile->GetType() == ObjType::NonWalkable)
	{
		m_isMoving = false;
		switch (_dir)
		{
		case DIR::UP:
			m_yBoxPos += 1;
			break;
		case DIR::DOWN:
			m_yBoxPos -= 1;
			break;
		case DIR::LEFT:
			m_xBoxPos += 1;
			break;
		case DIR::RIGHT:
			m_xBoxPos -= 1;
			break;
		}

		return false;
	}

	return true;
}
