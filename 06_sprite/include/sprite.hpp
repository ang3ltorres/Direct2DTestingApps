#pragma once

#include <wincodec.h>
#include "graphics.hpp"

class Sprite
{
public:
	Graphics* gfx;
	ID2D1Bitmap* bmp;

	Sprite(wchar_t* filename, Graphics* gfx);
	~Sprite();
	void draw();
};
