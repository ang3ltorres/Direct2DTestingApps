#pragma once

#include "game_level.hpp"
#include "graphics.hpp"

class GameController
{
private:
	GameController() = default;
public:
	~GameController() = default;

	static bool loading;
	static GameLevel* currentLevel;

	static void init();

	static void loadInitialLevel(GameLevel* level);
	static void switchLevel(GameLevel* level);

	static void update();
	static void render(Graphics* gfx);
};