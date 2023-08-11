#pragma once

typedef struct HWND__* HWND;
struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;
struct ID2D1BitmapRenderTarget;
struct ID2D1Bitmap;

class Graphics
{
public:
	Graphics(HWND& hwnd);
	~Graphics();

	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	ID2D1BitmapRenderTarget* renderTexture;
	ID2D1Bitmap* bitmapRenderTexture;
};
