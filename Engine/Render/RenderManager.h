#pragma once

#include <vector>

#include "SmartPointer/WeakPointer.h"
#include "GameObject/GameObject.h"
#include "Render/Renderer.h"
#include "JobSystem/Thread/Mutex.h"
#include "JobSystem/Thread/SingleWriterMultipleReader.h"

namespace Engine
{

	class RenderManager
	{
	private: 
		static RenderManager* m_Instance;
		SingleWriterMutipleReader* m_Mutex;

	public:
		RenderManager();
		~RenderManager();

		void Init();
		void Run();
		void ShutDown();

		static RenderManager* Instance();

		std::vector<Renderer*> Renderers;

		GLib::Sprites::Sprite* CreateSprite(const char* i_FileName);
		void AddRenderer(SharedPointer<GameObject> go, const char* i_FileName);
	};

}

#include "Render/RenderManager_inl.h"