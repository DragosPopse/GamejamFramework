#include "SDL.h"
#include "Gamejam/Demo/DemoGame.h"

jam::demo::DemoGame::DemoGame()
{
	Info info;
	info.width = 600;
	info.height = 400;
	info.title = "Demo Game";
	info.flags = SDL_WINDOW_SHOWN;
	info.fixedDelta = 1.f / 60.f;

	Init(info);
}
