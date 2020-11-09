#include <Gamejam/Core/Core.hpp>
#include <Gamejam/Core/Entry.hpp>
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

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

	protected:
		void Init(const App::Info& info);

	private:
		void Run();

	private:
		float m_fixedDelta = 0.f;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		bool m_running = false;
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}