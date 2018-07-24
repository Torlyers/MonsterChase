#include "Profiler.h"


namespace Engine	
{
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

	}
}
