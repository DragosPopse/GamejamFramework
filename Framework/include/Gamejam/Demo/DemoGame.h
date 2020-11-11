#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/Core/App.hpp"
#include "SDL.h"

namespace jam::demo
{
	class DemoShooter : public App
	{
	public:
		DemoShooter()
		{
			Info info;
			info.width = 600;
			info.height = 400;
			info.title = "Gamer";
			info.flags = SDL_WINDOW_SHOWN;
			info.fixedDelta = 1.f / 60.f;

			Init(info);
		}
	};
}
