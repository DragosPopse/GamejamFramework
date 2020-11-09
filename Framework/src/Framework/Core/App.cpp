#include <Gamejam/Core/App.hpp>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>


namespace jam
{
	App* App::s_instance = nullptr;


	App& App::Get()
	{
		return *s_instance;
	}


	void App::Init(const Info& info)
	{
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		m_fixedDelta = info.fixedDelta;
		m_width = info.width;
		m_height = info.height;

		m_window = SDL_CreateWindow(info.title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info.width, info.height, info.flags);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	}


	App::~App()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void App::Run()
	{
		m_running = true;

		while (m_running)
		{
			SDL_Event ev;

			while (SDL_PollEvent(&ev))
			{
				m_manager.HandleEvent(ev);
			}

			m_manager.Update(0.2f);

			SDL_RenderClear(m_renderer);
			m_manager.Render();
			SDL_RenderPresent(m_renderer);
		}
	}


	void App::SetEntryScene(std::shared_ptr<Scene> scene)
	{
		m_manager.PushScene(std::move(scene));
	}
}