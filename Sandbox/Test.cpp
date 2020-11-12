#include <iostream>
#include <Gamejam/Core/App.hpp>
#include <Gamejam/Core/Entry.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <Gamejam/SceneManagement/Scene.hpp>



class Entry :
    public jam::Scene
{
public:
    bool Update(float dt) override
    {
        printf("bruh\n");

        return false;
    }
};

JAM_ENTRY_SCENE(Entry)


class Application :
    public jam::App
{
public:
    Application()
    {
        App::Info info;
        info.width = 600;
        info.height = 400;
        info.title = "Gamer";
        info.flags = SDL_WINDOW_SHOWN;
        info.fixedDelta = 1.f / 60.f;

        Init(info);
    }
};
JAM_APP(Application)