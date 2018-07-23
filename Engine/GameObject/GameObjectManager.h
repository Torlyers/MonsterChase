#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "GameObject/GameObject.h"
#include "Physics/PhysicsManager.h"
#include "lua.hpp"
#include "Input/Input.h"
#include "SmartPointer/SharedPointer.h"
#include "Render/RenderManager.h"
#include "Base/Singleton.h"

namespace Engine
{
<<<<<<< HEAD
	class GameObjectManager final : public Singleton<GameObjectManager>
	{	
=======

	class GameObjectManager
	{
	private:

		static GameObjectManager* m_Instance;
		SingleWriterMutipleReader* m_Mutex;


>>>>>>> parent of 56cd134... debug
	public:
		friend Singleton<GameObjectManager>;

		GameObjectManager();
		~GameObjectManager();

		std::unordered_map<std::string, SharedPointer<GameObject>> GameObjects;

		void Init();
		void Run();
		void ShutDown();
<<<<<<< HEAD
			
		SharedPointer<GameObject>& CreateGameObjectFromLua(std::string i_FileName);
		void ReadFloatArray(lua_State* i_lua_state, int i_index, float* o_array, int num);

		inline vector<SharedPointer<GameObject>>& GetObjects();

	private:
		vector<SharedPointer<GameObject>> m_GameObjects;
	};
}

#include "GameObject/GameObjectManager_inl.h"
=======

		static GameObjectManager* Instance();

		void CreateGameObject(std::string i_Name, uint8_t* i_pFileContents, size_t i_FileSize);
		void ReadFloatArray(lua_State* i_lua_state, int i_index, float* o_array, int num);

		void AddGameObject(SharedPointer<GameObject> go, std::string i_Name);
	};

}
>>>>>>> parent of 56cd134... debug
