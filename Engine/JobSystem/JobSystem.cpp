#include "JobSystem.h"

#include <Windows.h>
#include <map>


#include "JobRunner.h"
#include "SharedJobQueue.h"

namespace Engine
{
namespace JobSystem
{



struct JobRunnerData
{
	HANDLE				m_ThreadHandle;
	DWORD				m_ThreadID;
	JobRunnerInput		m_Input;
};

struct JobQueueData
{
	SharedJobQueue		m_SharedQueue;
	std::vector<JobRunnerData *>	m_Runners;
};

std::map<HashedString, JobQueueData *>*	Queues;

void Init()
{
	Queues = new std::map<HashedString, JobQueueData *>();
}

void Shutdown()
{
	DEBUG_LOG( "Job System: Shutting down.\n" );

	IJob::Shutdown();

	std::vector<HANDLE>	AllThreads;

	std::map<HashedString, JobQueueData *>::iterator iter = Queues->begin();
	while( iter != Queues->end() )
	{

		if( iter->second )
		{
			const size_t count = iter->second->m_Runners.size();
			for( size_t i = 0; i < count; i++ )
			{
				JobRunnerData * pRunner = iter->second->m_Runners[i];
				if( pRunner  && pRunner->m_ThreadHandle != nullptr )
					AllThreads.push_back( pRunner->m_ThreadHandle );
			}

			iter->second->m_SharedQueue.Shutdown();
		}
		++iter;
	}

	DEBUG_LOG( "Job System: Waiting for Queue runner threads to shut down.\n" );

	DWORD result = WaitForMultipleObjects( static_cast<DWORD>( AllThreads.size() ), &AllThreads[0], TRUE, INFINITE );
	ASSERT( result == WAIT_OBJECT_0 );

	iter = Queues->begin();
	while( iter != Queues->end() )
	{
		if( iter->second )
		{
			const size_t count = iter->second->m_Runners.size();
			for( size_t i = 0; i < count; i++ )
			{
				JobRunnerData * pRunner = iter->second->m_Runners[i];
				if( pRunner )
					delete pRunner;
			}

			delete iter->second;
		}

		++iter;
	}
	
	Queues->clear();

	delete Queues;

}

void AddRunner( JobQueueData & i_QueueData )
{
	size_t runners = i_QueueData.m_Runners.size();

	JobRunnerData * pNewRunner = new JobRunnerData;
	
	pNewRunner->m_Input.i_pQueue = &i_QueueData.m_SharedQueue;
#ifdef _DEBUG
	const size_t	sizeThreadName = 32;
	char			ThreadName[sizeThreadName];
	sprintf_s( ThreadName, sizeThreadName, "%s %d", i_QueueData.m_SharedQueue.GetName(), int( runners + 1 ) );
	pNewRunner->m_Input.m_ThreadName = ThreadName;
#endif

	pNewRunner->m_ThreadHandle = CreateThread( nullptr, 0, JobRunner, &pNewRunner->m_Input, CREATE_SUSPENDED, &pNewRunner->m_ThreadID );
	ASSERT( pNewRunner->m_ThreadHandle != nullptr );

	i_QueueData.m_Runners.push_back( pNewRunner );
	ResumeThread( pNewRunner->m_ThreadHandle );
}

void AddRunner( const HashedString & i_QueueName )
{
	std::map<HashedString, JobQueueData *>::iterator existing = Queues->find( i_QueueName );
	ASSERT( existing != Queues->end() );
	ASSERT( existing->second );

	AddRunner( *existing->second );
}

void CreateQueue( const char * i_pName, unsigned int i_numRunners )
{
	ASSERT( i_pName );
	
	HashedString	HashedName( i_pName );

	ASSERT( Queues->find( HashedName ) == Queues->end() );

	JobQueueData * pNewJobQueueData = new JobQueueData;
	pNewJobQueueData->m_SharedQueue.SetName( i_pName );

	(*Queues)[HashedName] = pNewJobQueueData;

	for( unsigned int i = 0; i < i_numRunners; i++ )
		AddRunner( *pNewJobQueueData );
}

void RunJob( IJob * i_pJob, const HashedString & i_QueueName )
{
	ASSERT(i_pJob);
	std::map<HashedString, JobQueueData *>::iterator existing = Queues->find( i_QueueName );
	ASSERT( existing != Queues->end() );
	ASSERT( existing->second );

	DEBUG_LOG( "Job System: Adding Job to Queue \"%s\".\n", existing->second->m_SharedQueue.GetName() );
	existing->second->m_SharedQueue.Add( i_pJob );
}

} // namespace JobSystem
} // namespace Engine

