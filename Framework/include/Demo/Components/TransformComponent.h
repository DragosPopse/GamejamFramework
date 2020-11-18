#pragma once

namespace jam::demo
{
	class TransformSystem;

	class TransformComponent final
	{
		friend TransformSystem;

	public:
		float m_x = 0;
		float m_y = 0;

		float m_degrees = 0;
		float m_scale = 1;

		int32_t m_xScale = 1;
		int32_t m_yScale = 1;

		int32_t m_parent = -1;

	private:
		float m_xPrevious = 0;
		float m_yPrevious = 0;

		float m_xDelta = 0;
		float m_yDelta = 0;
	};
}