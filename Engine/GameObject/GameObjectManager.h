#pragma once
#include <vector>
#include <string>
#include <memory>
#include "GameObject/GameObject.h"
#include "Physics/PhysicsManager.h"
#include "lua.hpp"
#include "Input/Input.h"
#include "Render/RenderManager.h"
#include "Base/Singleton.h"

using namespace std;

namespace Engine
{

	class GameObjectManager : public Singleton<GameObjectManager>
	{
	private:

		vector<shared_ptr<GameObject>> m_GameObjects;

	public:
		GameObjectManager();
		~GameObjectManager();

		void Init();
		void Run();
		void ShutDown();
			
		shared_ptr<GameObject>& CreateGameObjectFromLua(std::string i_FileName);
		void ReadFloatArray(lua_State* i_lua_state, int i_index, float* o_array, int num);

		inline vector<shared_ptr<GameObject>>& GetObjects();
	};

}

#include "GameObject/GameObjectManager_inl.h"