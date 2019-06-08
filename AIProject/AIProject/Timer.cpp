#include "Timer.h"

void Timer::Start()
{
	m_lastTime = high_resolution_clock::now(); //Gets the current tick
}

float Timer::GetDeltaTime()
{
	m_currentTime = high_resolution_clock::now(); //Gets the current tick
	m_deltaTime = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>> (m_currentTime - m_lastTime);

	m_lastTime = m_currentTime;

	return m_deltaTime.count();
}