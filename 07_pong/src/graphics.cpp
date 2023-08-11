#include "graphics.hpp"

#include <Windows.h>
#include <d2d1.h>

Graphics::Graphics(HWND& hwnd)
{
	// Create factory
	const D2D1_FACTORY_OPTIONS factoryOptions = { .debugLevel = D2D1_DEBUG_LEVEL_NONE };
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, factoryOptions, &factory);

	// Create render target
	RECT rect;
	GetClientRect(hwnd, &rect);
	const D2D1_RENDER_TARGET_PROPERTIES rtProperties =
	{
		.type = D2D1_RENDER_TARGET_TYPE_HARDWARE,
		.pixelFormat = { .format = DXGI_FORMAT_UNKNOWN, .alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED },
		.dpiX = 0.0f,
		.dpiY = 0.0f,
		.usage = D2D1_RENDER_TARGET_USAGE_NONE,
		.minLevel = D2D1_FEATURE_LEVEL_10
	};

	const D2D1_HWND_RENDER_TARGET_PROPERTIES hwndRtProperties =
	{
		.hwnd = hwnd,
		.pixelSize = { .width = (UINT32)rect.right, .height = (UINT32)rect.bottom },
		.presentOptions = D2D1_PRESENT_OPTIONS_NONE
	};

	factory->CreateHwndRenderTarget(rtProperties, hwndRtProperties, &renderTarget);

	// Create default brush
	const D2D1_COLOR_F color = { .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 0.0f };
	renderTarget->CreateSolidColorBrush(color, &brush);


	/*DEBUG*/
	
	D2D1_PIXEL_FORMAT pixelFormatRenderTexture =
	{
		.format = DXGI_FORMAT_UNKNOWN,
		.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED
	};

	D2D1_SIZE_U sizeRenderTexture =
	{
		.width = 100,
		.height = 100
	};

	renderTarget->CreateCompatibleRenderTarget(
		nullptr,
		&sizeRenderTexture,
		&pixelFormatRenderTexture,
		D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
		&renderTexture
	);

	renderTexture->GetBitmap(&bitmapRenderTexture);
	/**/
}

Graphics::~Graphics()
{
	bitmapRenderTexture->Release();
	renderTexture->Release();
	brush->Release();
	renderTarget->Release();
	factory->Release();
}
