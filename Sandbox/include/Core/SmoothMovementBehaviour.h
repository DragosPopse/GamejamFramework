#pragma once
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "SmoothMovement.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam
{
	class SmoothMovementBehaviour final : public jecs::ISystemBehaviour<SmoothMovement>
	{
	public:
		SmoothMovementBehaviour(jecs::SystemManager& manager);
		void Update(float deltaTime);
	};
}
