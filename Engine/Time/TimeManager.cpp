#include "TimeManager.h"


namespace Engine
{

	TimeManager* TimeManager::m_Instance = nullptr;

	TimeManager* TimeManager::Instance()
	{
		if (m_Instance == nullptr)
			m_Instance = new TimeManager();
		return m_Instance;
	}

	TimeManager::TimeManager():
	GameTotalTime(0),
	FrameAmount(0),
	AverageFrameTime(0.0f),
	FrameRate(0.0f)
	{

		QueryPerformanceCounter(&FrameStartTime);
		QueryPerformanceCounter(&FrameEndTime);
	}

	TimeManager::~TimeManager()
	{
		
	}

	void TimeManager::Init()
	{

	}

	void TimeManager::Update()
	{
		//update Counter
		FrameStartTime = FrameEndTime;
		QueryPerformanceCounter(&FrameEndTime);
		
		//calculate this frame's time(ms)
		QueryPerformanceFrequency(&Frequency);
		FrameDeltaTime.QuadPart = FrameEndTime.QuadPart - FrameStartTime.QuadPart;
		FrameDeltaTime.QuadPart *= 1000000;
		FrameDeltaTime.QuadPart /= Frequency.QuadPart;
		DeltaTime = static_cast<double>(FrameDeltaTime.QuadPart);
		DeltaTime /= 1000000.0f;
		//DEBUG_LOG("%f", DeltaTime);

		//calculate frame rate
		FrameAmount += 1.0f;
		GameTotalTime += DeltaTime;
		AverageFrameTime = GameTotalTime / FrameAmount;
		FrameRate = 1.0f / AverageFrameTime;
		//DEBUG_LOG("%f", FrameRate);
	}

	void TimeManager::Shutdown()
	{
		if(m_Instance != nullptr)
			delete m_Instance;
	}
}
