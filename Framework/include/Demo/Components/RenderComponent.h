#pragma once
#include "SDL.h"

namespace jam::demo
{
	class RenderComponent final
	{
	public:
		SDL_Texture* m_texture = nullptr;
		int32_t m_scale = 1;
		float m_degrees = 0;

		int32_t m_xOffset = 0;
		int32_t m_yOffset = 0;

		int32_t m_index = 0;
		int32_t m_count = 1;

		bool m_xCenter = true;
		bool m_yCenter = true;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
	};
}
