#pragma once
#include "cECSar/IModule.h"

namespace jam::demo
{
	class TimeModule final : public cecsar::IModule
	{
	public:
		float timeScale = 1;

		float deltaTime = 1;
		float fixedDeltaTime = 1;
		float time = 0;
	};
}
