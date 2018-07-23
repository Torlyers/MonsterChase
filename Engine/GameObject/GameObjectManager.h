#pragma once
#include <vector>
#include <string>
#include "GameObject/GameObject.h"
#include "Physics/PhysicsManager.h"
#include "lua.hpp"
#include "Input/Input.h"
#include "SmartPointer/SharedPointer.h"
#include "Render/RenderManager.h"
#include "Base/Singleton.h"

using namespace std;

namespace Engine
{
	class GameObjectManager final : public Singleton<GameObjectManager>
	{	
	public:
		friend Singleton<GameObjectManager>;

		GameObjectManager();
		~GameObjectManager();

		void Init();
		void Run();
		void ShutDown();
			
		SharedPointer<GameObject>& CreateGameObjectFromLua(std::string i_FileName);
		void ReadFloatArray(lua_State* i_lua_state, int i_index, float* o_array, int num);

		inline vector<SharedPointer<GameObject>>& GetObjects();

	private:
		vector<SharedPointer<GameObject>> m_GameObjects;
	};
}

#include "GameObject/GameObjectManager_inl.h"