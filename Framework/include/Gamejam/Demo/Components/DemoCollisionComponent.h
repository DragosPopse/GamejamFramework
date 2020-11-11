#pragma once
#include <Gamejam/Core/Config.hpp>
#include <cstdint>
#include <vector>

namespace jam::demo
{
	constexpr auto COLLISION_LAYER_DEFAULT = 1;

	class DemoCollisionComponent final
	{
	public:
		int32_t layer = COLLISION_LAYER_DEFAULT;
		int32_t ignoredLayers = 0;

		float xScale = 16;
		float yScale = 16;

		bool isStatic = false;
		bool isTrigger = false;

		std::vector<int32_t> collisions;
	};
}
