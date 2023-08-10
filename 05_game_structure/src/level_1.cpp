#include "level_1.hpp"
#include "game_controller.hpp"
#include "graphics.hpp"

void Level1::load()
{
	y = 0.0f;
	ySpeed = 0.0f;
}

void Level1::unload()
{

}

void Level1::update()
{
	ySpeed += 1.0f;
	y += ySpeed;

	if (y > 600)
	{
		y = 600;
		ySpeed = -30.0f;
	}
}

void Level1::render(Graphics* gfx)
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	gfx->DrawCircle(375.0f, y, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}
