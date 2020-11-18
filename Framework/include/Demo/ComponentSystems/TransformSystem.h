#pragma once
#include "cECSar/IComponentSystem.h"

namespace jam::demo
{
	class TransformSystem final : public cecsar::IComponentSystem
	{
	public:
		void Update(cecsar::ECSystemManager& systemManager) override;
	};
}
