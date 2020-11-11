#pragma once

#include <Gamejam/Core/Config.hpp>
#include <memory>

union SDL_Event;

namespace jam
{
	class SceneManager;
	
	class Scene
	{
		friend class SceneManager;
	public:
		Scene() = default;

		virtual ~Scene() = default;

		/*
			A scene can control the behaviour of the SceneManager stack by returning true or false from these 4 functions.
			Scenes are updated from top to bottom. Returning false from any scene will result in the loop being terminated.
			Same thing happens with the render function, but it is looped from bottom to top.
			Use cases: Level scene returns true in it's render function so that you can still see the game faded out while in the pause menu.
					   Pause menu can return false in the Update function so that the game remains still. (It doesn't currently since the pause menu implements
					a slow motion effect)
		*/
		virtual bool HandleEvent(const SDL_Event& ev);
		virtual bool Update(float dt);
		virtual bool FixedUpdate(float dt);
		virtual bool Render();

		virtual void Enable();
		virtual void Disable();

		void RequestPush(std::shared_ptr<Scene> scene);
		void RequestPop();
		void RequestClear();

		//Is the scene on top of the stack? 
		bool OnTop() const;

	private:
		SceneManager* m_manager = nullptr;
	};
}