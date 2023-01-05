#include "CScene.h"
#include "CPlayer.h"
#include "CTile.h"
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
			tempVec.push_back(nullptr);
		m_vecObj.push_back(tempVec);
	}

	m_vecObj[0][0] = new CTile(0, 0);
	m_vecObj[0][1] = new CTile(0, 1);
	m_vecObj[1][1] = new CTile(1, 1);
}

CScene::~CScene()
{
}

void CScene::Input()
{
	m_player->Input();
}

void CScene::Update()
{
	m_player->Update();
}

void CScene::Render(ID2D1HwndRenderTarget* _renderTarget, ID2D1SolidColorBrush* _blackBrush)
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_vecObj[i][j] != nullptr)
				m_vecObj[i][j]->Render(_renderTarget);
			else
				_renderTarget->DrawRectangle(D2D1::RectF(j * 100, i * 100, (j * 100) + 100, (i * 100) + 100), _blackBrush);
		}
	}

	m_player->Render(_renderTarget);
}
