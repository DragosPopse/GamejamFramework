#pragma once
#include "Demo/ComponentSystems/TransformSystem.h"

namespace jam::demo
{
	class TransformComponent final
	{
	public:
		float xPos = 0;
		float yPos = 0;

		float xPosGlobal = 0;
		float yPosGlobal = 0;

		float depth = 0;

		float degrees = 0;
		float degreesGlobal;

		float xScale = 1;
		float yScale = 1;

		int32_t parent = -1;
	};
}
