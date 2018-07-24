#include "GameObjectManager.h"
#include "Math/Vector2.h"
#include "Colliders/BoxCollider2D.h"
#include "Colliders/ColliderManager.h"
#include "Message/MessageManager.h"


namespace Engine
{

	GameObjectManager* GameObjectManager::m_Instance = nullptr;

	GameObjectManager* GameObjectManager::Instance()
	{
		if (!m_Instance)
			m_Instance = new GameObjectManager();

		return m_Instance;
	}

	GameObjectManager::GameObjectManager()
	{
	}


	GameObjectManager::~GameObjectManager()
	{
	}

	void GameObjectManager::Init()
	{
		//m_Mutex = new Mutex(false, "AddGameObject");
		//m_Mutex = new SingleWriterMutipleReader();
	}

	void GameObjectManager::Run()
	{
		if (m_GameObjects.size() != 0)
		{
			/*if (Input::Instance()->isKeyDown)
			{
				Vector2 i_Force(100.0f, 0.0f);
				GameObjects[0]->GetRigidBody()->AddForce(i_Force);
			}
			else
			{
				Vector2 i_Force(0.0f, 0.0f);
				GameObjects[0]->GetRigidBody()->AddForce(i_Force);
			}*/
		}
	}

	void GameObjectManager::ShutDown()
	{
		for (int i = 0; i < m_GameObjects.size(); ++i)
		{
			m_GameObjects[i]->Shutdown();
		}
		
		if(m_Instance)
			delete m_Instance;
	}

	shared_ptr<GameObject>& GameObjectManager::CreateGameObjectFromLua(std::string i_FileName)
	{
		size_t fileSize = 0;
		uint8_t* pFileContents = LoadFile(i_FileName.c_str(), fileSize);

		if (pFileContents && fileSize)
		{
			//temp varables
			const char* pVersion;
			const char* pName;
			Vector2 initPosition;
			float rotation;
			Vector2 size;
			float mass;
			float drag;
			Vector2 velocity;
			const char* pSpritePath;


			//create lua state
			lua_State* p_lua_state = luaL_newstate();
			ASSERT(p_lua_state);
			luaL_openlibs(p_lua_state);


			int result = 0;
			result = luaL_loadbuffer(p_lua_state, reinterpret_cast<char*>(pFileContents), fileSize, nullptr);
			ASSERT(result == 0);
			result = lua_pcall(p_lua_state, 0, 0, 0);//check error
			ASSERT(result == 0);

			//read version information
			result = lua_getglobal(p_lua_state, "Version");
			if (result == LUA_TSTRING)
			{
				const char* temp = lua_tostring(p_lua_state, -1);
				pVersion = _strdup(temp);
			}
			lua_pop(p_lua_state, 1);

			//get player
			result = lua_getglobal(p_lua_state, "Player");
			ASSERT(result == LUA_TTABLE);

			//get name			
			lua_pushstring(p_lua_state, "name");
			result = lua_gettable(p_lua_state, -2);
			if (result == LUA_TSTRING)
			{
				const char* temp = lua_tostring(p_lua_state, -1);
				pName = _strdup(temp);
			}
			else
			{
				DEBUG_LOG("No Name Information");
				pName = _strdup("None");
			}
			lua_pop(p_lua_state, 1);


			//get initial position
			lua_pushstring(p_lua_state, "position");
			result = lua_gettable(p_lua_state, -2);
			if (result == LUA_TTABLE)
			{
				float position[3];
				ReadFloatArray(p_lua_state, -1, position, 3);
				initPosition.x(position[0]);
				initPosition.y(position[1]);
			}
			else
			{
				DEBUG_LOG("No Position Information");
				initPosition.x(0.0f);
				initPosition.y(0.0f);
			}
			lua_pop(p_lua_state, 1);


			//get rotation
			lua_pushstring(p_lua_state, "rotation");
			result = lua_gettable(p_lua_state, -2);
			if (result == LUA_TNUMBER)
			{
				rotation = lua_tonumber(p_lua_state, -1);
			}
			else
			{
				DEBUG_LOG("No Rotation Information");
				rotation = 0.0f;
			}
			lua_pop(p_lua_state, 1);


			//use the data to init gameobject
			shared_ptr<GameObject> gameobject(new GameObject(initPosition));
			m_GameObjects.push_back(gameobject);
			gameobject->SetName(pName);
			gameobject->SetPosition(initPosition);
			gameobject->SetRotation(rotation);



			//read collider information
			lua_pushstring(p_lua_state, "Collider");
			result = lua_gettable(p_lua_state, -2);
			if (result == LUA_TTABLE)
			{
				lua_pushstring(p_lua_state, "isCollider");
				result = lua_gettable(p_lua_state, -2);
				bool isCollider = lua_toboolean(p_lua_state, -1);
				lua_pop(p_lua_state, 1);
				if (isCollider)
				{
					lua_pushstring(p_lua_state, "size");
					result = lua_gettable(p_lua_state, -2);
					if (result == LUA_TTABLE)
					{
						float position[3];
						ReadFloatArray(p_lua_state, -1, position, 3);
						size.x(position[0]);
						size.y(position[1]);
					}
					else
					{
						DEBUG_LOG("No Size Information");
						size.x(0.0f);
						size.y(0.0f);
					}
					lua_pop(p_lua_state, 1);


					//init Collider
					ColliderManager::Instance()->AddCollider(gameobject);
					Vector3 center(0.0f, size.y() / 2.0f, 0.0f);
					Vector3 extent(size.x() / 2.0f, size.y() / 2.0f, 0.0f);
					BoxCollider2D* collider = gameobject->GetCollider();
					AABB aabb(center, extent);
					collider->SetAABB(aabb);


				}
				else
				{
					DEBUG_LOG("GameObject has no collider");
				}

			}
			else
			{
				DEBUG_LOG("No Collision Information");
			}
			lua_pop(p_lua_state, 1);



			//get rigidbody information
			lua_pushstring(p_lua_state, "Rigidbody");
			result = lua_gettable(p_lua_state, -2);
			if (result == LUA_TTABLE)
			{
				lua_pushstring(p_lua_state, "isRigidbody");
				result = lua_gettable(p_lua_state, -2);
				bool isRigidbody = lua_toboolean(p_lua_state, -1);
				lua_pop(p_lua_state, 1);
				if (isRigidbody)
				{
					//read mass
					lua_pushstring(p_lua_state, "mass");
					result = lua_gettable(p_lua_state, -2);
					if (result == LUA_TNUMBER)
					{
						mass = lua_tonumber(p_lua_state, -1);
					}
					lua_pop(p_lua_state, 1);

					//read drag
					lua_pushstring(p_lua_state, "drag");
					result = lua_gettable(p_lua_state, -2);
					if (result = LUA_TNUMBER)
					{
						drag = lua_tonumber(p_lua_state, -1);
					}
					lua_pop(p_lua_state, 1);

					//read initial velocity
					lua_pushstring(p_lua_state, "velocity");
					result = lua_gettable(p_lua_state, -2);
					if (result = LUA_TTABLE)
					{
						float vel[3];
						ReadFloatArray(p_lua_state, -1, vel, 3);
						velocity.x(vel[0]);
						velocity.y(vel[1]);
					}
					lua_pop(p_lua_state, 1);


					//init Rigidbody
					PhysicsManager::Instance()->AddRigidBody(gameobject);
					gameobject->GetRigidBody()->SetMass(mass);
					gameobject->GetRigidBody()->SetDragFactor(drag);
					gameobject->GetRigidBody()->SetVelocity(velocity);
				}
				else
				{
					DEBUG_LOG("GameObject has no rigidbody");
				}

			}
			else
			{
				DEBUG_LOG("No Rigidbody Information");
			}
			lua_pop(p_lua_state, 1);



			//get render information
			lua_pushstring(p_lua_state, "Renderer");
			result = lua_gettable(p_lua_state, -2);
			if (result == LUA_TTABLE)
			{

				lua_pushstring(p_lua_state, "isRenderer");
				result = lua_gettable(p_lua_state, -2);
				bool isRenderer = lua_toboolean(p_lua_state, -1);
				lua_pop(p_lua_state, 1);
				if (isRenderer)
				{
					lua_pushstring(p_lua_state, "sprite_path");
					result = lua_gettable(p_lua_state, -2);
					if (result == LUA_TSTRING)
					{
						const char* temp = lua_tostring(p_lua_state, -1);
						pSpritePath = _strdup(temp);
					}
					else
					{
						DEBUG_LOG("No Sprite Path Information");
						pSpritePath = _strdup("None");
					}
					lua_pop(p_lua_state, 1);

					//init Renderer
					RenderManager::Instance()->AddRenderer(gameobject, pSpritePath);
				}
				else
				{
					DEBUG_LOG("Gameobject has no renderer");
					pSpritePath = _strdup("None");
				}

			}
			else
			{
				DEBUG_LOG("No Render Information");
			}
			lua_pop(p_lua_state, 1);

			lua_pop(p_lua_state, 1);

			ASSERT(lua_gettop(p_lua_state) == 0);

			lua_close(p_lua_state);

			delete[] pVersion;
			delete[] pName;
			delete[] pSpritePath;
			delete[] pFileContents;

			return gameobject;

		}
	}

	
	void GameObjectManager::ReadFloatArray(lua_State* i_lua_state, int i_index, float* o_array, int num)
	{
		lua_pushnil(i_lua_state);

		size_t index = 0;
		while (lua_next(i_lua_state, i_index - 1) != 0)
		{
			ASSERT(lua_type(i_lua_state, -1) == LUA_TNUMBER);
			o_array[index++] = lua_tonumber(i_lua_state, -1);
			lua_pop(i_lua_state, 1);

			if (index >= num)
				break;
		}

		lua_pop(i_lua_state, 1);

	}
}