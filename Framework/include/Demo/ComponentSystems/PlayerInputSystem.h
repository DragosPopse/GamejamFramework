#pragma once
#include "cECSar/IComponentSystem.h"
#include "Demo/Components/ControllerComponent.h"

namespace jam::demo
{
	class PlayerInputSystem final : public cecsar::IComponentSystem
	{
	public:
		void Update(cecsar::ECSystemManager& systemManager) override;

	private:
		ControllerComponent GetUpdatedController();
	};
}
