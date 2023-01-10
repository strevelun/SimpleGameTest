#pragma once
#include <windows.h>


#include "CScene.h"
#include "CPlayer.h"


#define MAX_LOADSTRING 100
#define WIDTH           1200
#define HEIGHT          880


class CApp
{
private:
	static CApp* m_inst;

	WCHAR szTitle[MAX_LOADSTRING] = {};
	WCHAR szWindowClass[MAX_LOADSTRING] = {};

	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;


	int m_mouseX, m_mouseY;
	int m_mag = 100; // 확대, 축소 배율

private:
	CApp() { }
	~CApp() {}


public:
	static CApp* GetInstance()
	{
		if (m_inst == nullptr)  m_inst = new CApp();
		return m_inst;
	}

	HRESULT Init(HINSTANCE hInstance, int nCmdShow);
	void Input();
	void Update();
	void Render();
	int Run();


	LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};