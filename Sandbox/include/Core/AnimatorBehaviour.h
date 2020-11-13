#pragma once
#include "Gamejam/JECS/Core/ISystemBehaviour.h"
#include "AnimatorComponent.h"
#include "Gamejam/JECS/Core/SystemManager.h"

namespace jam
{
	class AnimatorBehaviour final : public jecs::ISystemBehaviour<AnimatorComponent>
	{
	public:
		AnimatorBehaviour(jecs::SystemManager& manager);
		void Update(float deltaTime);
	};
}
