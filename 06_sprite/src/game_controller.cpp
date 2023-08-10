#include "game_controller.hpp"

bool GameController::loading;
GameLevel* GameController::currentLevel;

void GameController::init()
{
	loading = true;
	currentLevel = nullptr;
}

void GameController::loadInitialLevel(GameLevel* level)
{
	loading = true;
	currentLevel = level;
	currentLevel->load();
	loading = false;
}

void GameController::switchLevel(GameLevel* level)
{
	loading = true;
	currentLevel->unload();
	delete currentLevel;
	currentLevel = level;
	currentLevel->load();
	loading = false;
}

void GameController::update() { currentLevel->update(); }
void GameController::render() { currentLevel->render(); }
