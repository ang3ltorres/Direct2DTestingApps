#include "graphics.hpp"

#include <Windows.h>
#include <d2d1.h>

// Static members
ID2D1Factory* Graphics::factory = nullptr;
ID2D1HwndRenderTarget* Graphics::render = nullptr;
ID2D1SolidColorBrush* Graphics::brush = nullptr;

// Struct Color
Color::Color()
: r(0), g(0), b(0), a(0) {}

Color::Color(const Color& other)
: r(other.r), g(other.g), b(other.b), a(other.a) {}

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
: r(r), g(g), b(b), a(a) {}

// Struct Vector2
Vector2::Vector2()
: x(0.0f), y(0.0f) {}

Vector2::Vector2(const Vector2& other)
: x(other.x), y(other.y) {}

Vector2::Vector2(float x, float y)
: x(x), y(y) {}

// Struct Rect
Rect::Rect()
: pos(0.0f, 0.0f), size(0.0f, 0.0f) {}

Rect::Rect(const Rect& other)
: pos(other.pos), size(other.size) {}

Rect::Rect(float x, float y, float w, float h)
: pos(x, y), size(w, h) {}

Rect::Rect(const Vector2& pos, const Vector2& size)
: pos(pos), size(size) {}

void Rect::draw(const Color& color)
{
	Graphics::brush->SetColor({color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f});
	Graphics::render->FillRectangle({pos.x, pos.y, pos.x + size.x, pos.y + size.y}, Graphics::brush);
}

void Graphics::initialize(HWND& hwnd)
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

	factory->CreateHwndRenderTarget(rtProperties, hwndRtProperties, &render);

	// Create default brush
	const D2D1_COLOR_F color = { .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 0.0f };
	render->CreateSolidColorBrush(color, &brush);
}

void Graphics::finalize()
{
	brush->Release();
	render->Release();
	factory->Release();
}
