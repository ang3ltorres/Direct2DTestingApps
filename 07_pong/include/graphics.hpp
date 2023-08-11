#pragma once

#include <cstdint>

typedef struct HWND__* HWND;
struct ID2D1Factory;
struct ID2D1HwndRenderTarget;
struct ID2D1SolidColorBrush;

struct Color
{
	Color();
	Color(const Color& other);
	Color(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0, std::uint8_t a = 255);
	~Color() = default;

	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
	std::uint8_t a;
};

struct Vector2
{
	Vector2();
	Vector2(const Vector2& other);
	Vector2(float x, float y);
	~Vector2() = default;

	float x;
	float y;
};

struct Rect
{
	Rect();
	Rect(const Rect& other);
	Rect(float x, float y, float w, float h);
	Rect(const Vector2& pos, const Vector2& size);
	~Rect() = default;

	Vector2 pos;
	Vector2 size;

	void draw(const Color& color);
};

class Graphics
{
private:
	Graphics() = default;
	~Graphics() = default;
	
public:
	static void initialize(HWND& hwnd);
	static void finalize();

	static ID2D1Factory* factory;
	static ID2D1HwndRenderTarget* render;
	static ID2D1SolidColorBrush* brush;
};
