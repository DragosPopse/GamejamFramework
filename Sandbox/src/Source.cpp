#include "Gamejam/Core/Entry.hpp"
#include <SDL_vulkan.h>
#include "Gamejam/Core/App.hpp"
#include "Gamejam/SceneManagement/Scene.hpp"
#include "cECSar/ECSystemManager.h"


namespace jam
{
    class Application :
            public App
    {
    public:
        Application()
        {
            Info info;
            info.width = 32*20;
            info.height = 32*20;
            info.title = "Gamer";
            info.flags = SDL_WINDOW_SHOWN;
            info.fixedDelta = 1.f / 60.f;

            Init(info);
        }
    };

	class MainScene final : public Scene
	{
		cecsar::ECSystemManager manager = cecsar::ECSystemManager(1000);
	};
}

JAM_ENTRY_SCENE(jam::MainScene)
JAM_APP(jam::Application)