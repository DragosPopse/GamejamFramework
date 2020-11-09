#pragma once
#include <SDL.h>

namespace jam
{
	namespace JECS
	{
		namespace Examples
		{
			class ExRenderer final
			{
			public:
				SDL_Texture* texture = nullptr;
				int32_t index = 0, count = 1;
				float xOffset = 0, yOffset = 0;
				bool xCenter = true, yCenter = true;

				SDL_RendererFlip flip = SDL_FLIP_NONE;
				float angle = 0;
				float scale = 1;
			};
		}
	}
}
