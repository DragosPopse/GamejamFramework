#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/Demo/DemoRenderComponent.h"
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam::demo
{
	class DemoRenderBehaviour final : public jecs::ISystemBehaviour<DemoRenderComponent>
	{
	public:
		DemoRenderBehaviour(jecs::SystemManager& manager);
		void Update();
	};
}
