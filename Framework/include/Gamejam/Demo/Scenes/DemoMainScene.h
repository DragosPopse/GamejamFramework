#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/SceneManagement/Scene.hpp"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Factories/DemoDummyFactory.h"
#include "Gamejam/Demo/Behaviours/DemoControllerBehaviour.h"

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
		DemoControllerBehaviour* m_controllerBehaviour = nullptr;
		DemoDummyFactory* m_dummyFactory = nullptr;
	};
}
