#pragma once

namespace jam::demo
{
	class TransformSystem;

	class TransformComponent final
	{
		friend TransformSystem;

	public:
		float x = 0;
		float y = 0;

		float degrees = 0;

		float xScale = 1;
		float yScale = 1;

		int32_t parent = -1;

	private:
		float m_xPrevious = 0;
		float m_yPrevious = 0;

		float m_degreesPrevious = 0;
		float m_xScalePrevious = 1;
		float m_yScalePrevious = 1;

		float m_xDelta = 0;
		float m_yDelta = 0;

		float m_degreesDelta = 0;
		float m_xScaleDelta = 0;
		float m_yScaleDelta = 0;
	};
}