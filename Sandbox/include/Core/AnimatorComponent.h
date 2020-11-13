﻿#pragma once
#include <cstdint>

namespace jam
{
	class AnimatorComponent final
	{
	public:
		float speed = 1;
		bool loop = true;
		bool paused = false;

		int32_t from = 0, to = -1;
		float lerp = 0;
	};
}