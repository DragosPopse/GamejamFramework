#pragma once

#include <Gamejam/Core/Core.hpp>

namespace jam
{
	class App;
	class Scene;
}	

int main(int argc, char** argv);


jam::App* CreateApp();
jam::Scene* CreateEntryScene();

#define JAM_APP(AppClass) jam::App* CreateApp() { return new AppClass(); }
#define JAM_ENTRY_SCENE(SceneClass) jam::Scene* CreateEntryScene() { return new SceneClass(); }
