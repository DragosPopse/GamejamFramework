#pragma once
#include "cECSar/IComponentSystem.h"

namespace jam::demo
{
	class CameraSystem final : public cecsar::IComponentSystem
	{
	public:
		void Update(cecsar::ECSystemManager& systemManager) override;
	};
}
