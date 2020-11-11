#pragma once

#include <chrono>


namespace jam
{
	using Seconds = std::chrono::duration<float>;

	template <typename Clock = std::chrono::steady_clock>
	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}


		jam::Seconds Reset()
		{
			auto elapsed = GetElapsed();
			m_start = Clock::now();
			return elapsed;
		}


		jam::Seconds GetElapsed() const
		{
			auto now = Clock::now();
			jam::Seconds diff = now - m_start;
			return diff;
		}


	private:
		typename Clock::time_point m_start;
	};
}


