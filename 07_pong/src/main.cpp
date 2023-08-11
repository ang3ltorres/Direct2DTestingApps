#include "graphics.hpp"

#include <Windows.h>
#include <d2d1.h>

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
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);
	RECT rect = { 0, 0, 800, 800 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"D2D", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	msg.message = WM_NULL;

	Graphics* gfx = new Graphics(hwnd);

	float pos = 0.0f;

	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return 0;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		pos += 1.0f;

		gfx->renderTarget->BeginDraw();
		gfx->renderTarget->Clear(D2D1::ColorF(0.0f, 1.0f, 1.0f));

		gfx->brush->SetColor(D2D1::ColorF(1.0f, 0.0f, 0.0f));
		gfx->renderTarget->FillRectangle(D2D1::RectF(pos, pos, pos + 50.0f, pos + 50.0f), gfx->brush);

		gfx->renderTarget->EndDraw();

	}

	delete gfx;
	UnregisterClass(windowClass.lpszClassName, hInstance);
	return 0;
}