#include <Gamejam/Resources/Texture.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <Gamejam/Core/App.hpp>


namespace jam
{
	Texture::~Texture()
	{
		Reset();
	}


	void Texture::Reset()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
			m_width = 0;
			m_height = 0;
		}
	}


	uint32_t Texture::GetWidth() const
	{
		return m_width;
	}


	uint32_t Texture::GetHeight() const
	{
		return m_height;
	}


	SDL_Texture* Texture::GetRaw() const
	{
		return m_texture;
	}


	bool Texture::LoadFromFile(const char* file)
	{
		Reset();
		SDL_Surface* surface = IMG_Load(file);
		if (surface)
		{
			m_texture = SDL_CreateTextureFromSurface(App::Get().m_renderer, surface);
			m_width = surface->w;
			m_height = surface->h;
			SDL_FreeSurface(surface);
			return true;
		}
		return false;
	}
}