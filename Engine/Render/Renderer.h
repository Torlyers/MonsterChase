#pragma once

#include "SmartPointer/WeakPointer.h"
#include "GameObject/gameobject.h"
#include "GLib.h"

namespace Engine
{
	class Renderer
	{
	private:

		WeakPointer<GameObject> m_GameObject;
		GLib::Sprites::Sprite* m_Sprite;

	public:
		Renderer();
		Renderer(SharedPointer<GameObject> i_GameObject);
		~Renderer();

		WeakPointer<GameObject> GetGameObject();
		void SetGameObject(SharedPointer<GameObject> i_GameObject);

		GLib::Sprites::Sprite* GetSprite();
		void SetSprite(GLib::Sprites::Sprite* i_sprite);

		void Init();
		void Run();
		void ShutDown();
	};
}

#include "Renderer_inl.h"



