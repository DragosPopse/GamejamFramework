#pragma once
#include <cstdint>

namespace jam::demo
{
	class ControllerComponent final
	{
	public:
		float xDir = 0;
		float yDir = 0;

		int32_t xMouse = 0;
		int32_t yMouse = 0;

		bool lMouse = false;
		bool rMouse = false;

		bool shift = false;
		bool space = false;
	};
};