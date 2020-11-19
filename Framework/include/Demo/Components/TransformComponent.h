#pragma once

namespace jam::demo
{
	class TransformComponent final
	{
	public:
		float xPos = 0;
		float yPos = 0;

		float xPosGlobal = 0;
		float yPosGlobal = 0;

		float degrees = 0;
		float degreesGlobal;

		float xScale = 1;
		float yScale = 1;

		float xScaleGlobal = 0;
		float yScaleGlobal = 0;

		float depth = 0;

		int32_t parent = -1;
	};
}
