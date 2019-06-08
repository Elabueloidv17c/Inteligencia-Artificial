#pragma once
#include "Headers.h"

static class Timer
{
	duration <double, std::ratio<1>>	m_deltaTime;
	TimePoint							m_lastTime;	
	TimePoint							m_currentTime;

public:

	Timer() = default;
	~Timer() = default;

	void								Start();
	float								GetDeltaTime();	
};


