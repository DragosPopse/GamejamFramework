#pragma once
#include <Gamejam/Core/Config.hpp>
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam::demo
{
	class DemoCollisionBehaviour final : public jecs::ISystemBehaviour<DemoCollisionBehaviour>
	{
	public:
		DemoCollisionBehaviour(jecs::SystemManager& manager);
		void Update();
	};
}
