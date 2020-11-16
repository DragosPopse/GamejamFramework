#pragma once
#include "cECSar/IComponentSystem.h"

namespace jam::demo
{
	class RenderSystem final : public cecsar::IComponentSystem
	{
	public:
		RenderSystem(cecsar::ECSystemManager& manager);

		void Update(cecsar::ECSystemManager& systemManager) override;
	};
}
