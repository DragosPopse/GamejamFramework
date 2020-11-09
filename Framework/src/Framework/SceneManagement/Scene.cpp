#include <Gamejam/SceneManagement/Scene.hpp>
#include <Gamejam/SceneManagement/SceneManager.hpp>
#include <SDL.h>


namespace jam
{
	void Scene::RequestPush(std::shared_ptr<Scene> scene)
	{
		m_manager->PushScene(scene);
	}


	void Scene::RequestPop()
	{
		m_manager->PopScene();
	}


	void Scene::RequestClear()
	{
		m_manager->Clear();
	}


	bool Scene::OnTop() const
	{
		return m_manager->Top() == this;
	}


	bool Scene::HandleEvent(const SDL_Event&)
	{
		return false;
	}


	bool Scene::Update(float)
	{
		return false;
	}


	bool Scene::FixedUpdate(float)
	{
		return false;
	}


	bool Scene::Render()
	{
		return false;
	}


	void Scene::Enable()
	{
	}


	void Scene::Disable()
	{
	}
}


