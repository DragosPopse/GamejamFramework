#include <Gamejam/Resources/Font.hpp>
#include <SDL_ttf.h>

namespace jam
{
	Font::~Font()
	{
		Reset();
	}


	void Font::Reset()
	{
		if (m_font)
		{
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}
	}


	bool Font::LoadFromFile(const char* file, uint32_t pointSize)
	{
		Reset();
		m_font = TTF_OpenFont(file, pointSize);

	}


	TTF_Font* Font::GetRaw() const
	{
		return m_font;
	}
}