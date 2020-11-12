#include "Precomp/Precomp.h"
#include "Core/Scenes.h"

JAM_ENTRY_SCENE(jam::EntryScene)

namespace jam
{
    class Application :
            public App
    {
    public:
        Application()
        {
            App::Info info;
            info.width = 32*20;
            info.height = 32*20;
            info.title = "Gamer";
            info.flags = SDL_WINDOW_SHOWN;
            info.fixedDelta = 1.f / 60.f;

            Init(info);
        }
    };
}

JAM_APP(jam::Application)