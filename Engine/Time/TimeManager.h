#pragma once
#include <windows.h>
#include <WinBase.h>
#include <iostream>
#include "DebugTool/Debug.h"

namespace Engine
{

	class TimeManager
	{
	
	private:

		static TimeManager* m_Instance;

		typedef LARGE_INTEGER Tick;

		Tick FrameStartTime;
		Tick FrameEndTime;
		Tick FrameDeltaTime;
		Tick Frequency;

		double FrameRate;
		double FrameAmount;
		double DeltaTime;
		double AverageFrameTime;
		double GameTotalTime;		
	
	public:

		TimeManager();
		~TimeManager();

		//For engine loop
		void Init();
		void Update();
		void Shutdown();

		//Singleton
		static TimeManager* Instance();

		//Getters
		float GetFrameDeltaTime();
		float GetFrameRate();

		float GetTimeDiff_ms(Tick i_Counter);
		Tick GetCurrentTickCounter();
		
	};
}

#include "Time/TimeManager_inl.h"