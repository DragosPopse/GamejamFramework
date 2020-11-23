#pragma once
#include "Gamejam/Core/App.hpp"
#include "SDL.h"

namespace jam::demo
{
	class DemoApp final : public App
	{
	public:
		DemoApp()
		{
			Info info;
			info.width = 32 * 20;
			info.height = 32 * 20;
			info.title = "Demo Game";
			info.flags = SDL_WINDOW_SHOWN;
			info.fixedDelta = 1.f / 60.f;

			Init(info);
		}
	};
}
