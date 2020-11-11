#pragma once
#include <Gamejam/Core/Config.hpp>
#include <string>
#include <map>
#include "SDL.h"

namespace jam::demo
{
	class DemoTextureLib final
	{
	public:
		static DemoTextureLib& Get();
		SDL_Texture* GetTexture(const std::string key);
		void Clear();

	private:
		std::map<std::string, SDL_Texture*> m_textureMap;
	};
}