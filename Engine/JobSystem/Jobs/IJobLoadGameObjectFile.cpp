#include "IJobLoadGameObjectFile.h"
#include "JobSystem/Jobs/IJobProcessGameObjectFile.h"
#include "JobSystem/JobSystem.h"

namespace Engine
{
	namespace JobSystem
	{
		IJobLoadGameObjectFile::IJobLoadGameObjectFile(std::string i_Name, const char* i_pFileName) :
			IJob("LoadGameObjectFile"),
			m_pFileName(i_pFileName),
			m_Name(i_Name)
		{

		}

		void IJobLoadGameObjectFile::Run()
		{
			size_t fileSize = 0;
			uint8_t* p_FileContents = LoadFile(m_pFileName, fileSize);

			if (p_FileContents && fileSize)
			{
				IJob* pProcessJob = new IJobProcessGameObjectFile(m_Name, p_FileContents, fileSize);
				ASSERT(pProcessJob);

				Engine::JobSystem::RunJob(pProcessJob, "CreateGameObject");

			}
		}
	}
}
