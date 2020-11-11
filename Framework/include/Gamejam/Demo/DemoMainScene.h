#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/SceneManagement/Scene.hpp"
#include "Gamejam/JECS/Core/SystemManager.h"
#include <Gamejam/Demo/DemoRenderBehaviour.h>
#include "DemoDummyFactory.h"

namespace jam::demo
{
	class DemoMainScene final : public Scene
	{
	public:
		DemoMainScene();
		~DemoMainScene();

		void Enable() override;
		void Disable() override;

		bool Update(float deltaTime) override;
		bool Render() override;

	private:
		jecs::SystemManager* m_systemManager = nullptr;
		DemoRenderBehaviour* m_renderBehaviour = nullptr;
		DemoDummyFactory* m_dummyFactory = nullptr;
	};
}
