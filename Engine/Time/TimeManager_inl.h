#pragma once
#include "Time/TimeManager.h"

namespace Engine
{
	inline float TimeManager::GetFrameDeltaTime()
	{
		return DeltaTime;
	}

	inline float TimeManager::GetFrameRate()
	{
		return FrameRate;
	}

	inline TimeManager::Tick TimeManager::GetCurrentTickCounter()
	{
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return counter;
	}

	inline float TimeManager::GetTimeDiff_ms(TimeManager::Tick i_Counter)
	{
		LARGE_INTEGER currentPerformanceCounter, frequency, elapsedTime;

		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&currentPerformanceCounter);

		elapsedTime.QuadPart = (currentPerformanceCounter.QuadPart - i_Counter.QuadPart);
		elapsedTime.QuadPart *= 1000000.0f;
		elapsedTime.QuadPart /= frequency.QuadPart;

		return elapsedTime.QuadPart / 1000.0f;
	}
}