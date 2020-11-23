#pragma once
#include <cstdint>

namespace jam::demo
{
	class AnimatorSystem;

	class AnimatorComponent
	{
		friend AnimatorSystem;

	public:
		int32_t from = 0, to = -1;
		float speed = 5;

	private:
		float m_lerp = 0;
	};
}
