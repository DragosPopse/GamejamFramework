#pragma once
#include "cECSar/IComponentSystem.h"

namespace jam::demo
{
	class RenderSystem final : public cecsar::IComponentSystem
	{
	public:
		void Update(cecsar::ECSystemManager& systemManager) override;
	};
}
