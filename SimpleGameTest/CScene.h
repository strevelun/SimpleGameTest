#pragma once

#include <d2d1.h>
#include <vector>
#include <stdexcept>

class CTile;
class CPlayer;

enum class OBJ
{
	None,
	Player,
	Tile,
};

class CScene
{
	static CScene* m_inst;

	// 현재 배율. 25%, 50%, 100%, 125%, 200%
	CPlayer* m_player = nullptr;
	std::vector<std::vector<CTile*>> m_vecObj;

	int m_width = 0, m_height = 0;

public:
	CScene();
	~CScene();

	static CScene* GetInst()
	{
		if (m_inst == nullptr)
			m_inst = new CScene();
		return m_inst;
	}

	void Input();
	void Update();
	void Render(ID2D1HwndRenderTarget* _renderTarget, ID2D1SolidColorBrush* _blackBrush);
	CTile* GetTileAtPos(int _x, int _y) {

		//try {
			CTile* tile = m_vecObj[_y][_x];
		//}
		//catch (const std::out_of_range& e) 
		//{
		//	return nullptr;
		//}

		return m_vecObj[_y][_x];
	}
};

