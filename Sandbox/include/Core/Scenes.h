#include <Precomp/Precomp.h>
#include "Managers/TileMapper.h"

namespace jam
{
	class EntryScene :
		public Scene
	{
	public:
		void Enable() override
		{
			m_tileMapper = TileMapper::GetInstance();
		}

		bool HandleEvent(const SDL_Event& ev) override
		{
			// Get input.

			return true;
		}

		bool Render() override
		{
			// Render stuff.

			return true;
		}

	private:
		TileMapper* m_tileMapper;
	};

	class MainScene :
		public Scene
	{
	public:
		bool HandleEvent(const SDL_Event& ev) override
		{
			// Get input.

			return true;
		}

		bool Update(float dt) override
		{
			// Do stuff.

			return true;
		}

		bool Render() override
		{
			// Render stuff.

			return true;
		}
	};
}