#pragma once
#include "AntBrain.h"
#include "Gamejam/JECS/Core/SystemManager.h"
#include "Gamejam/JECS/Core/ISystemBehaviour.h"

namespace jam
{
	class AntBehaviour final : public jecs::ISystemBehaviour<AntBrain>
	{
	public:
		AntBehaviour(jecs::SystemManager& manager);
		void Update(float deltaTime);
	};
}
