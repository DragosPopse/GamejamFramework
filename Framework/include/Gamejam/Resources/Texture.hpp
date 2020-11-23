#pragma once
#include <Gamejam/Core/Config.hpp>
#include <SDL_blendmode.h>

struct SDL_Texture;
struct SDL_Renderer;



namespace jam
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool LoadFromFile(const char* file);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		SDL_Texture* GetRaw() const;


		void Reset();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void SetBlendMode(SDL_BlendMode blend);

		

	private:
		SDL_Texture* m_texture = nullptr;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
	};
}