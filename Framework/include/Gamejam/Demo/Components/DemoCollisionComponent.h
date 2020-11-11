#pragma once
#include <Gamejam/Core/Config.hpp>

namespace jam::demo
{
	class DemoCollisionComponent final
	{
	public:
		float xScale = 1;
		float yScale = 1;

		bool isStatic = false;
		bool isTrigger = false;
	};
}