#pragma once
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "SandBrain.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam 
{
	class SandBehaviour final : public jecs::ISystemBehaviour<SandBrain>
	{
	public:
		SandBehaviour(jecs::SystemManager& manager);
		void Update();
	};
}
