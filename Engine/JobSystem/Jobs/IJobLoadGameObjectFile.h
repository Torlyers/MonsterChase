#pragma once
#include "JobSystem/IJob.h"
#include "File/File.h"
#include "DebugTool/Debug.h"
#include <string>

namespace Engine
{

	namespace JobSystem
	{
		class IJobLoadGameObjectFile : public IJob 
		{
		public:

			IJobLoadGameObjectFile(std::string i_Name, const char* i_pFileName);

			void Run() override;

		private:
			const char* m_pFileName;
			std::string m_Name;
			
		};
	}

}

