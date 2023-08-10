#include <Windows.h>
#include "Graphics.hpp"
#include "level_1.hpp"
#include "game_controller.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"D2D", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);

	Graphics* graphics = new Graphics();
	if (!graphics->init(hwnd))
	{
		delete graphics;
		return -1;
	}

	GameLevel::init(graphics);
	
	ShowWindow(hwnd, nCmdShow);

	GameController::loadInitialLevel(new Level1());

	MSG msg;
	msg.message = WM_NULL;

	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return 0;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		GameController::update();

		graphics->BeginDraw();
		GameController::render();
		graphics->EndDraw();

	}

	delete graphics;
	return 0;
}