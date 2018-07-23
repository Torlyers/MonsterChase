#include "IJobProcessGameObjectFile.h"
#include "DebugTool/Debug.h"
#include "Engine/Engine.h"


namespace Engine
{
	namespace JobSystem
	{

		IJobProcessGameObjectFile::IJobProcessGameObjectFile(std::string i_Name, uint8_t* i_pFileContents, size_t i_fileSize):
			IJob("ProcessGameObjectFile"),
			m_fileSize(i_fileSize),
			m_pFileContents(i_pFileContents),
			m_Name(i_Name)
		{

		}

		void IJobProcessGameObjectFile::Run()
		{
			GameObjectManager::Instance()->CreateGameObject(m_Name, m_pFileContents, m_fileSize);
		}
	}
}