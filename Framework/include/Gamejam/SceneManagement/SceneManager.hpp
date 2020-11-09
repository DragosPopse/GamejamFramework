#pragma once

#include <Gamejam/Core/Core.hpp>
#include <memory>
#include <list>
#include <queue>

union SDL_Event;

namespace jam
{
	class Scene;

	class SceneManager
	{
		enum class ChangeType
		{
			Push,
			Pop,
			Clear
		};
		struct PendingChange
		{
			ChangeType type;
			std::shared_ptr<Scene> scene;

			PendingChange(ChangeType t, std::shared_ptr<Scene> s = nullptr) :
				type(t),
				scene(s)
			{
			}
		};

	public:
		SceneManager() = default;
		~SceneManager() = default;

		void PushScene(std::shared_ptr<Scene> scene);
		void PopScene();
		void Clear();


		bool IsEmpty() const { return m_stack.empty(); }


		void HandleEvent(const SDL_Event& ev);
		void Update(float dt);
		void FixedUpdate(float dt);
		void Render();


		const Scene* Top() const;

	private:
		void ApplyChanges();
		
	private:


		std::list<std::shared_ptr<Scene>> m_stack;
		std::queue<PendingChange> m_pendingChanges;
	};
}