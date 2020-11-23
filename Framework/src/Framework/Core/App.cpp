#include <Gamejam/Core/App.hpp>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <Gamejam/Core/Time.hpp>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <imgui_sdl.h>
#include <SDL_ttf.h>


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
		TTF_Init();
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
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void App::Run()
	{
		ImGui::CreateContext();
		ImGuiSDL::Initialize(m_renderer, m_width, m_height);
		bool running = true;
		float timeSinceLastFrame = 0.f;
		jam::Timer timer;
		while (running)
		{
			ImGuiIO& io = ImGui::GetIO();
			(void)io;
			float dt = timer.Reset().count();
			int wheel = 0;
			timeSinceLastFrame += dt;
			SDL_Event ev;
			while (SDL_PollEvent(&ev))
			{
				ImGui_ImplSDL2_ProcessEvent(&ev);
				
				
				m_manager.HandleEvent(ev);
			}

			int mouseX, mouseY;
			const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

			// Setup low-level inputs (e.g. on Win32, GetKeyboardState(), or write to those fields from your Windows message loop handlers, etc.)

			io.DeltaTime = 1.0f / 60.0f;
			io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
			io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
			io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
			io.MouseWheel = static_cast<float>(wheel);

			m_manager.Update(dt);
			while (timeSinceLastFrame > m_fixedDelta)
			{
				timeSinceLastFrame -= m_fixedDelta;
				m_manager.FixedUpdate(m_fixedDelta);
			}

			if (m_manager.IsEmpty())
			{
				running = false;
			}

			ImGui::NewFrame();

			SDL_RenderClear(m_renderer);
			m_manager.Render();
			ImGui::Render();
			ImGuiSDL::Render(ImGui::GetDrawData());
			//ImGui::EndFrame();
			SDL_RenderPresent(m_renderer);
			
		}
	}


	void App::SetEntryScene(std::shared_ptr<Scene> scene)
	{
		m_manager.PushScene(std::move(scene));
	}
}