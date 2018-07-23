#pragma once

#include "GameObject/gameobject.h"
#include "GLib.h"
#include <memory>
using namespace std;

namespace Engine
{
	class Renderer
	{
	private:

		weak_ptr<GameObject> m_GameObject;
		GLib::Sprites::Sprite* m_Sprite;

	public:
		Renderer();
		Renderer(shared_ptr<GameObject> i_GameObject);
		~Renderer();

		weak_ptr<GameObject> GetGameObject();
		void SetGameObject(shared_ptr<GameObject> i_GameObject);

		GLib::Sprites::Sprite* GetSprite();
		void SetSprite(GLib::Sprites::Sprite* i_sprite);

		void Init();
		void Run();
		void ShutDown();
	};
}

#include "Renderer_inl.h"



