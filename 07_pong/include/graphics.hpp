#pragma once

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
public:
	Graphics(HWND& hwnd);
	~Graphics();

	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
};
