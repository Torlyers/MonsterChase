#pragma once
#include "Time/TimeManager.h"
#include <map>

namespace Engine
{

	class Accumulator
	{
	public:

		double		m_Sum;
		uint64_t	m_Count;
		float		m_Min, m_Max;

		Accumulator();
		Accumulator(const char* iName);
		void operator+=(float i_time);
		float Average();
	};

	class ScopedTimer
	{
	private:

		LARGE_INTEGER	m_Start;
		Accumulator*	m_Accumulator;
		const char*	    m_ScopeName;

	public:
		ScopedTimer(const char* i_Name, Accumulator & i_MyAccumulator);
		~ScopedTimer();
		
	};

	class Profiler
	{
	private:
		std::map<const char *, Accumulator *> m_AllAccumulators;	
		static Profiler* m_Instance;

	public:
		~Profiler();
		void RegisterAccumulator(const char * i_Name, Accumulator* i_Accumulator);
		void OutputProfile();
		static Profiler* Instance();

		void Init();
		void Shutdown();
	};

}

#ifdef PROFILE
#define PROFILE_UNSCOPED(name)					\
	static Engine::Accumulator myAccumulator(name);	\
	Engine::ScopedTimer myTimer(name, myAccumulator);

#define PROFILE_SCOPED_BEGIN(name) {\
	static Engine::Accumulator myAccumulator(name);	\
	Engine::ScopedTimer myTimer(name, myAccumulator);

#define PROFILE_SCOPED_END() }
#else
#define PROFILE_UNSCOPED(name) __noop
#define PROFILE_SCOPED_BEGIN(name) __noop
#define PROFILE_SCOPED_END() __noop
#endif

#include "Profiling/Profiler_inl.h"
