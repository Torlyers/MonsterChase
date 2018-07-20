#include "Profiler.h"


namespace Engine	
{
	Profiler* Profiler::m_Instance = nullptr;

	Profiler* Profiler::Instance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new Profiler();
		}

		return m_Instance;
	}

	void Profiler::RegisterAccumulator(const char * i_Name, Accumulator* i_Accumulator)
	{
		m_AllAccumulators[i_Name] = i_Accumulator;
	}

	void Profiler::OutputProfile()
	{
#ifdef PROFILE

		for (auto accumulator : m_AllAccumulators)
		{
			PROFILE_LOG("Profile: %s, Total Time: %f, Average Time: %f", accumulator.first, accumulator.second->m_Sum, accumulator.second->Average());
		}
#endif
	}

	void Profiler::Init()
	{

	}

	void Profiler::Shutdown()
	{
		if (m_Instance)
			delete m_Instance;
	}

}
