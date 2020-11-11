#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "Gamejam/Demo/Components/DemoControllerComponent.h"

namespace jam::demo
{
	class DemoControllerBehaviour final : public jecs::ISystemBehaviour<DemoControllerComponent>
	{
	public:
		DemoControllerBehaviour(jecs::SystemManager& manager);
		void Update(float deltaTime);
	};
}
