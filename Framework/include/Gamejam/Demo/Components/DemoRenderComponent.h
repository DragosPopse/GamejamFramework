#pragma once
#include <Gamejam/Core/Config.hpp>
#include "SDL.h"

namespace jam::demo
{
	class DemoRenderComponent final
	{
	public:
		SDL_Texture* texture;
	};
}
