#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
public:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	Graphics();
	~Graphics();

	bool init(HWND hwnd);

	void BeginDraw();
	void EndDraw();

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
};
