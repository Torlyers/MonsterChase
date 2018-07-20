#pragma once
#include<cinttypes>
#include"JobSystem/IJob.h"
#include "GameObject/GameObjectManager.h"

namespace Engine
{
	namespace JobSystem
	{


		class IJobProcessGameObjectFile : public IJob 
		{
		public:
			IJobProcessGameObjectFile(std::string i_Name, uint8_t* i_pFileContents, size_t i_fileSize);

			void Run() override;

		private:
			uint8_t* m_pFileContents;
			size_t m_fileSize;
			std::string m_Name;
		};

	}
}
