#include <Gamejam/SceneManagement/SceneManager.hpp>
#include <Gamejam/SceneManagement/Scene.hpp>
#include <SDL.h>
#include <Gamejam/Adaptors/Reverse.hpp>

namespace jam
{

	void SceneManager::PushScene(std::shared_ptr<Scene> scene)
	{
		scene->m_manager = this;
		m_pendingChanges.push(PendingChange(ChangeType::Push, std::move(scene)));
	}


	void SceneManager::PopScene()
	{
		m_pendingChanges.push(PendingChange(ChangeType::Pop));
	}


	void SceneManager::Clear()
	{
		m_pendingChanges.push(PendingChange(ChangeType::Clear));
	}


	void SceneManager::Update(float dt)
	{
		ApplyChanges();
		for (auto& scene : jam::adapt::Reverse(m_stack))
		{
			if (!scene->Update(dt))
			{
				return;
			}
		}
	}


	void SceneManager::FixedUpdate(float dt)
	{
		ApplyChanges();
		for (auto& scene : jam::adapt::Reverse(m_stack))
		{
			if (!scene->FixedUpdate(dt))
			{
				return;
			}
		}
	}


	void SceneManager::Render()
	{
		for (auto& scene : m_stack)
		{
			if (!scene->Render())
			{
				return;
			}
		}
	}


	void SceneManager::HandleEvent(const SDL_Event& ev)
	{
		ApplyChanges();
		for (auto& scene : jam::adapt::Reverse(m_stack))
		{
			if (!scene->HandleEvent(ev))
			{
				return;
			}
		}
	}


	void SceneManager::ApplyChanges()
	{
		bool c = false;
		while (!m_pendingChanges.empty())
		{
			c = true;
			PendingChange change = m_pendingChanges.front();
			m_pendingChanges.pop();
			switch (change.type)
			{
			case ChangeType::Push:
			{
				std::shared_ptr<Scene> ptr(change.scene);
				ptr->Enable();
				m_stack.push_back(std::move(ptr));
			}
			break;

			case ChangeType::Pop:
				if (!m_stack.empty())
				{
					m_stack.back()->Disable();
					m_stack.pop_back();
				}
				break;

			case ChangeType::Clear:
				if (!m_stack.empty())
				{
					for (auto& scene : jam::adapt::Reverse(m_stack))
					{
						scene->Disable();
					}
					m_stack.clear();
				}
				break;
			}
		}
	}


	const Scene* SceneManager::Top() const
	{
		return m_stack.back().get();
	}
}