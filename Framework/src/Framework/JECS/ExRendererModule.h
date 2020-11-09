#pragma once
#include <cstdint>
#include <SDL.h>
#include <string>
#include <map>

namespace DJ
{
	namespace JECS
	{
		namespace Examples
		{
			class ExRendererModule final
			{
			public:
				const int32_t WIDTH, HEIGHT;
				float angle = 0;
				float zoom = 1;

				ExRendererModule(int32_t w = 800, int32_t h = 600);

				void PreRender() const;
				void PostRender() const;

				SDL_Renderer& GetRenderer() const;
				SDL_Texture* GetTexture(const std::string& key);

			private:
				SDL_Window* _window = nullptr;
				SDL_Renderer* _renderer = nullptr;
				SDL_Texture* _texture = nullptr;

				std::map<std::string, SDL_Texture*> _textureMap;

				SDL_Texture& LoadTexture(const std::string& path) const;
			};
		}
	}
}
