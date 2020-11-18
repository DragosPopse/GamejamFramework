#pragma once
#include "cECSar/IModule.h"
#include "SDL.h"
#include <string>

namespace jam::demo
{
	class RenderModule final : public cecsar::IModule
	{
	public:
		SDL_Texture* GetTexture(std::string path);
	};
}
