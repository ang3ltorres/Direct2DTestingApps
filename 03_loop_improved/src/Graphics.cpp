#include "Graphics.hpp"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	if (brush) brush->Release();
	if (renderTarget) renderTarget->Release();
	if (factory) factory->Release();
}

bool Graphics::init(HWND hwnd)
{
	HRESULT res;
	res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(hwnd, &rect);
	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget
	);

	if (res != S_OK) return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;

	return true;
}

void Graphics::BeginDraw()
{
	renderTarget->BeginDraw();
}

void Graphics::EndDraw()
{
	renderTarget->EndDraw();
}

void Graphics::Render()
{
	BeginDraw();

	ClearScreen(1.0f, 0.0f, 1.0f);

	for (int i = 0; i < 1000; i++)
		DrawCircle(rand() % 800, rand() % 600, rand() % 100,
			(rand() % 100) / 100.0f,
			(rand() % 100) / 100.0f,
			(rand() % 100) / 100.0f,
			(rand() % 100) / 100.0f
		);

	EndDraw();
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

