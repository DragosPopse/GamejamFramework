#pragma once
#include <Gamejam/Core/Config.hpp>
#include <SDL_ttf.h>

namespace jam
{
	class Font
	{
	public:
		Font() = default;
		~Font();

		void Reset();

		bool LoadFromFile(const char* file, uint32_t pointSize);

		TTF_Font* GetRaw() const;

	private:
		TTF_Font* m_font = nullptr;
	};
}