#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/SceneManagement/Scene.hpp"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "SDL.h"
#include <Gamejam/Demo/DemoRenderBehaviour.h>

namespace jam::demo
{
	class DemoMainScene final : public Scene
	{
	public:
		DemoMainScene();
		~DemoMainScene();

		void Disable() override;

		bool Update(float deltaTime) override;
		bool Render() override;

	private:
		SDL_Texture& GetTexture(std::string key);

		jecs::SystemManager* m_systemManager = nullptr;
		std::map<std::string, SDL_Texture*> m_textureMap;
		DemoRenderBehaviour* m_renderBehaviour;
	};
}
