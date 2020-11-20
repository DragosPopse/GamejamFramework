#pragma once
#include "cECSar/IEntityFactory.h"

namespace jam::demo
{
	class PlayerCameraFactory final : public cecsar::IEntityFactory
	{
	public:
		void OnConstruction(cecsar::ECSystemManager& manager, int32_t index) override;
	};
}
