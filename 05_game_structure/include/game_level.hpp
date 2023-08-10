#pragma once

#include "graphics.hpp"

class GameLevel
{
public:
	GameLevel() = default;
	virtual ~GameLevel() = default;

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void update() = 0;
	virtual void render(Graphics* gfx) = 0;
};
