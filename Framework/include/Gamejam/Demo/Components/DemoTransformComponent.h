#pragma once
#include <Gamejam/Core/Config.hpp>

namespace jam::demo
{
	class DemoTransformComponent final
	{
	public:
		float x = 0, y = 0;
		float angle = 0;
		float xScale = 1;
		float yScale = 1;
	};
}