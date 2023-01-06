#pragma once

#include "CObj.h"

enum class ObjType
{
	None,
	Walkable,
	NonWalkable,
};

class CTile
	: public CObj
{
	ObjType m_type;

public:
	CTile(int _y, int _x, ObjType _type);
	~CTile();

	void Input();
	void Update();
	void Render(ID2D1HwndRenderTarget* _renderTarget, int _mag);

	ObjType GetType() const { return m_type; }
};

