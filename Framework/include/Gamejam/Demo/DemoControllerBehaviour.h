#pragma once
#include <Gamejam/Core/Config.hpp>
#include "DemoControllerComponent.h"
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam::demo
{
	class DemoControllerBehaviour final : public jecs::ISystemBehaviour<DemoControllerComponent>
	{
	public:
		DemoControllerBehaviour(jecs::SystemManager& manager);
		void Update(float deltaTime);
	};
}