#pragma once

#include <vector>
#include <Memory>
#include "GameObject/GameObject.h"
#include "Render/Renderer.h"
#include "Base/Singleton.h"

using namespace std;

namespace Engine
{

	class RenderManager : public Singleton<RenderManager>
	{
	private: 

	public:
		RenderManager();
		~RenderManager();

		void Init();
		void Run();
		void ShutDown();

		std::vector<Renderer*> Renderers;

		GLib::Sprites::Sprite* CreateSprite(const char* i_FileName);
		void AddRenderer(shared_ptr<GameObject> go, const char* i_FileName);
	};

}

#include "Render/RenderManager_inl.h"