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
	float rotation = 0.0f;

	/*DEBUG*/
	// We draw only one time
	gfx->renderTexture->BeginDraw();
	gfx->renderTexture->Clear(D2D1::ColorF(D2D1::ColorF::Yellow));
	gfx->brush->SetColor(D2D1::ColorF(1.0f, 0.0f, 1.0f));
	gfx->renderTexture->FillEllipse(D2D1::Ellipse(D2D1::Point2F(50.0f, 50.0f), 25.0f, 25.0f), gfx->brush);
	gfx->brush->SetColor(D2D1::ColorF(0.0f, 1.0f, 0.0f));
	gfx->renderTexture->FillEllipse(D2D1::Ellipse(D2D1::Point2F(50.0f, 50.0f), 10.0f, 10.0f), gfx->brush);
	gfx->renderTexture->EndDraw();
	/**/

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
		rotation += 2.0f;

		gfx->renderTarget->BeginDraw();
		gfx->renderTarget->Clear(D2D1::ColorF(0.0f, 1.0f, 1.0f));

		/*DEBUG*/
		// Draw the texture in the main target
		D2D1_MATRIX_3X2_F translationToCenter = D2D1::Matrix3x2F::Translation(-200.0f, -200.0f);
		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(rotation);
		D2D1_MATRIX_3X2_F translationBack = D2D1::Matrix3x2F::Translation(200.0f, 200.0f);

		gfx->renderTarget->SetTransform(translationToCenter * rotationMatrix * translationBack);
		gfx->renderTarget->DrawBitmap(gfx->bitmapRenderTexture, D2D1::RectF(0.0f, 0.0f, 400.0f, 400.0f), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		gfx->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		/**/

		gfx->brush->SetColor(D2D1::ColorF(1.0f, 0.0f, 0.0f));
		gfx->renderTarget->FillRectangle(D2D1::RectF(pos, pos, pos + 50.0f, pos + 50.0f), gfx->brush);

		gfx->renderTarget->EndDraw();

	}

	delete gfx;
	UnregisterClass(windowClass.lpszClassName, hInstance);
	return 0;
}