#pragma once

#include <chrono>

namespace ogle {

class Timer {

	private:
		using Clock = std::chrono::steady_clock;

	public:
		Timer();

		double FrameTime();
		void Reset();

	private:
		Clock::time_point m_last_time;
		Clock::time_point m_now;
};

} // namespace ogle
