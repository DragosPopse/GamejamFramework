#pragma once
#include "SDL.h"

namespace jam::demo
{
	class RenderComponent final
	{
	public:
		SDL_Texture* m_texture = nullptr;
	};
}
