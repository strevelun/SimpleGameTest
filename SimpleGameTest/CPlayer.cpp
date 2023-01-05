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
	// Ÿ�ϰ� �̵� �� �϶��� �̵�Ű�� ������ ����. �� �ѹ��� �Էµ�
	// ���� �̵��� �Ϸ��ߴٸ� update���� isMoving�� true
	// �̵�Ű�� ������ ���� �������� xBoxPos�� ������Ʈ�ǰ� 
	// �̵�Ű�� ������ �׳� ������ �� �������� �� �̵���Ű�鼭 �������� ��. 

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

void CPlayer::Update()
{
	char str[20] = "";
	switch (m_dir)
	{
	case DIR::UP:
		if (!CanGo(m_dir))
			break;

		m_ypos -= m_speed;
		if ((m_yBoxPos) * 100 >= m_ypos)
		{
			m_ypos = (m_yBoxPos) * 100;
			m_isMoving = false;
		}
		break;
	case DIR::DOWN:
		if (!CanGo(m_dir))
			break;

		m_ypos += m_speed;
		if (m_yBoxPos * 100 <= m_ypos)
		{
			m_ypos = m_yBoxPos * 100;
			m_isMoving = false;
		}
		break;
	case DIR::LEFT:
		if (!CanGo(m_dir))
			break;
		m_xpos -= m_speed;
		if ((m_xBoxPos) * 100 >= m_xpos)
		{
			m_xpos = (m_xBoxPos) * 100;
			m_isMoving = false;
		}
		break;
	case DIR::RIGHT:
		if (!CanGo(m_dir))
			break;

		m_xpos += m_speed;
		if (m_xBoxPos * 100 <= m_xpos)
		{
			m_xpos = m_xBoxPos * 100;
			m_isMoving = false;
		}
		break;
	}
}

void CPlayer::Render(ID2D1HwndRenderTarget* _renderTarget)
{
	m_bitmap->Render(_renderTarget, m_xpos, m_ypos, 100, 100);
}

bool CPlayer::CanGo(DIR _dir)
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
		if (m_ypos + m_speed > SCREEN_HEIGHT - 100)
		{
			m_isMoving = false;
			m_yBoxPos = (SCREEN_HEIGHT / 100) - 1;
			m_ypos = SCREEN_HEIGHT - 100;
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
		if (m_xpos + m_speed > SCREEN_WIDTH - 100)
		{
			m_isMoving = false;
			m_xBoxPos = (SCREEN_WIDTH / 100) - 1;
			m_xpos = SCREEN_WIDTH - 100;
			return false;
		}
		break;
	}

	CTile* tile = CScene::GetInst()->GetTileAtPos(m_xBoxPos, m_yBoxPos);
	if (tile == nullptr)
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
