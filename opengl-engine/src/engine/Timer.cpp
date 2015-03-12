#include "engine/Timer.h"

namespace ogle {

Timer::Timer() :
	m_last_time{Clock::now()},
	m_now{}
{
}

double Timer::FrameTime() {
	m_now = Clock::now();
	const auto difference = m_now - m_last_time;
	using target_duration = std::chrono::duration<double, std::ratio<1, 1>>;
	return std::chrono::duration_cast<target_duration>(difference).count();
}

void Timer::Reset() {
	m_last_time = m_now;
}

} // sdl2engine
