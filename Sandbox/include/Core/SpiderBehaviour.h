#pragma once
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include <Core\SpiderBrain.h>
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam
{
	class SpiderBehaviour final : jecs::ISystemBehaviour<SpiderBrain>
	{
	public:
		SpiderBehaviour(jecs::SystemManager& manager);
		void Update();
	};
}
