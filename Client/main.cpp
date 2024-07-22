#include "../Engine/pch.h"
#include "DemoApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	DemoApp gameApp;
	MSG msg;

	gameApp.Initialize(hInstance, nCmdShow);
	gameApp.Run(msg);
	gameApp.Uninitialize();

	return (int)msg.wParam;
}
