#include "CScene.h"
#include "CPlayer.h"
#include "Game.h"

#include <d2d1.h>

CScene* CScene::m_inst = nullptr;

CScene::CScene()
{
	m_player = new CPlayer();

	m_width = SCREEN_WIDTH / 100;
	m_height = SCREEN_HEIGHT / 100;

	for (int i = 0; i < m_height; i++)
	{
		std::vector<CTile*> tempVec;
		for (int j = 0; j < m_width; j++)
			tempVec.push_back(new CTile(i, j, ObjType::None));
		m_vecObj.push_back(tempVec);
	}

	m_vecObj[0][0] = new CTile(0, 0, ObjType::Walkable);
	m_vecObj[0][1] = new CTile(0, 1, ObjType::Walkable);
	m_vecObj[1][1] = new CTile(1, 1, ObjType::Walkable);
}

CScene::~CScene()
{
}

void CScene::Input()
{
	m_player->Input();
}

void CScene::Update(int _mag)
{
	m_player->Update(_mag);
}

void CScene::Render(ID2D1HwndRenderTarget* _renderTarget, ID2D1SolidColorBrush* _blackBrush, int _mag)
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_vecObj[i][j]->GetType() == ObjType::None || m_vecObj[i][j]->GetType() == ObjType::NonWalkable)
				_renderTarget->DrawRectangle(D2D1::RectF(j * _mag, i * _mag, (j * _mag) + _mag, (i * _mag) + _mag), _blackBrush);
			else if(m_vecObj[i][j]->GetType() == ObjType::Walkable)
				m_vecObj[i][j]->Render(_renderTarget, _mag);
		}
	}

	m_player->Render(_renderTarget, _mag);
}

void CScene::SetTile(int _x, int _y, ObjType _type)
{
	// try
	m_vecObj[_y][_x] = new CTile(_y, _x, _type);
}