#pragma once
#include <Gamejam/Core/Config.hpp>
#include <cstdint>
#include <vector>

namespace jam::demo
{
	class DemoCollisionComponent final
	{
	public:
		int32_t layer = 0;
		std::vector<int32_t> ignoredLayers;

		float xScale = 16;
		float yScale = 16;

		bool isStatic = false;
		bool isTrigger = false;

		std::vector<int32_t> collisions;
	};
}
