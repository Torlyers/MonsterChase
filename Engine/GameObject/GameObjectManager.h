#pragma once
#include <vector>
#include <string>
#include "GameObject/GameObject.h"
#include "Physics/PhysicsManager.h"
#include "lua.hpp"
#include "Input/Input.h"
#include "SmartPointer/SharedPointer.h"
#include "Render/RenderManager.h"
#include "JobSystem/Thread/Mutex.h"
#include "JobSystem/Thread/SingleWriterMultipleReader.h"


using namespace std;

namespace Engine
{

	class GameObjectManager
	{
	private:

		static GameObjectManager* m_Instance;
		vector<SharedPointer<GameObject>> m_GameObjects;


	public:
		GameObjectManager();
		~GameObjectManager();

		void Init();
		void Run();
		void ShutDown();

		static GameObjectManager* Instance();
			
		SharedPointer<GameObject>& CreateGameObjectFromLua(std::string i_FileName);
		void CreateGameObject(std::string i_Name, uint8_t* i_pFileContents, size_t i_FileSize);
		void ReadFloatArray(lua_State* i_lua_state, int i_index, float* o_array, int num);

		void AddGameObject(SharedPointer<GameObject> go, std::string i_Name);

		inline vector<SharedPointer<GameObject>>& GetObjects();
	};

}

#include "GameObject/GameObjectManager_inl.h"