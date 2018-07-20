#pragma once
#include "Profiling/Profiler.h"

namespace Engine
{

	inline Accumulator::Accumulator() :
		m_Sum(0.0),
		m_Count(0),
		m_Max(FLT_MAX),
		m_Min(FLT_MIN)
	{
		//gProfiler->RegisterAccumulator(i_Name, this);
	}

	inline Accumulator::Accumulator(const char* i_Name) :
		m_Sum(0.0),
		m_Count(0),
		m_Max(FLT_MAX),
		m_Min(FLT_MIN)
	{
		Profiler::Instance()->RegisterAccumulator(i_Name, this);
	}

	inline void Accumulator::operator+=(float i_time)
	{
		m_Sum += i_time;
		m_Count++;

		if (i_time > m_Max)
			m_Max = i_time;
		else if (i_time < m_Min)
			m_Min = i_time;
	}

	inline float Accumulator::Average()
	{
		return m_Sum / m_Count;
	}

	inline ScopedTimer::ScopedTimer(const char* i_Name, Accumulator & i_MyAccumulator) :
		m_Start(TimeManager::Instance()->GetCurrentTickCounter()),
		m_Accumulator(&i_MyAccumulator),
		m_ScopeName(i_Name)
	{}

	inline ScopedTimer::~ScopedTimer()
	{
		*m_Accumulator += TimeManager::Instance()->GetTimeDiff_ms(TimeManager::Instance()->GetCurrentTickCounter());
	}

	inline Profiler::~Profiler()
	{
		std::map<const char*, Accumulator*>::iterator itor = m_AllAccumulators.begin();
		while (itor != m_AllAccumulators.end())
		{
			itor->second = nullptr;
			m_AllAccumulators.erase(itor++);
		}
		m_AllAccumulators.clear();
	}
}