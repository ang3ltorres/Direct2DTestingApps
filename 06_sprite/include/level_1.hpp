#pragma once

#include "game_level.hpp"

class Level1 : public GameLevel
{
public:
	Level1() = default;
	virtual ~Level1() = default;

	float y;
	float ySpeed;
	Sprite* sprites;

	virtual void load() override;
	virtual void unload() override;
	virtual void update() override;
	virtual void render() override;
};
