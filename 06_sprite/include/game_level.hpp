#pragma once

#include "graphics.hpp"
#include "sprite.hpp"

class GameLevel
{
public:
	GameLevel() = default;
	virtual ~GameLevel() = default;

	static Graphics* gfx;
	static void init(Graphics* graphics);

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};
