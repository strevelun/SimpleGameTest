#include "CApp.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if(FAILED(CApp::GetInstance()->Init(hInstance, nCmdShow, 800, 600)))
		return 0;

	return CApp::GetInstance()->Run();
}

