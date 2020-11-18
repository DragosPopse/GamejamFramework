#pragma once

namespace jam::demo
{
	class TransformComponent final
	{
	public:
		float m_x = 0;
		float m_y = 0;

		float m_degrees = 0;
		float m_scale = 1;

		int32_t m_xScale = 1;
		int32_t m_yScale = 1;
	};
}