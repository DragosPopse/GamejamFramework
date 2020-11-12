#pragma once

#include <Gamejam/Core/Config.hpp>
#include <cstdint>
#include <Gamejam/SceneManagement/SceneManager.hpp>

struct SDL_Window;
struct SDL_Renderer;

int main(int argc, char** argv);

namespace jam
{
	class App
	{
		friend int ::main(int argc, char** argv);

	public:
		struct Info
		{
			uint32_t width;
			uint32_t height;
			uint32_t flags;
			const char* title;
			float fixedDelta;
		};

		App() = default;

		virtual ~App();

		static App& Get();

		SDL_Renderer* m_renderer = nullptr;

	protected:
		void Init(const App::Info& info);

	private:
		void Run();
		void SetEntryScene(std::shared_ptr<Scene> scene);

	public:
		static App* s_instance;


		float m_fixedDelta = 0.f;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		bool m_running = false;
		SDL_Window* m_window = nullptr;
		SceneManager m_manager;
	};
}