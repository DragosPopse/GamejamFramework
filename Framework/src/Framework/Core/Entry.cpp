#include <Gamejam/Core/Entry.hpp>
#include <Gamejam/Core/App.hpp>
#include <Gamejam/SceneManagement/Scene.hpp>
#include <memory>


int main(int argc, char** argv)
{
	jam::App::s_instance = CreateApp();
	auto* pscene = CreateEntryScene();
	std::shared_ptr<jam::Scene> scene(pscene);
	jam::App::s_instance->SetEntryScene(std::move(scene));
	jam::App::s_instance->Run();
	delete jam::App::s_instance;

	return 0;
}