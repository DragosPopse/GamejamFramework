#pragma once
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "GravityComponent.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam
{
	class GravityBehaviour final : public jecs::ISystemBehaviour<GravityComponent>
	{
	public:
		GravityBehaviour(jecs::SystemManager& manager);
		void Update(float deltaTime);
	};
}