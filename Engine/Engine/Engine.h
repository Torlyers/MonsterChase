#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>

#include "GameObject\gameobject.h"
#include "Time\TimeManager.h"
#include "Physics\PhysicsManager.h"
#include "Input\Input.h"
#include "SmartPointer\SharedPointer.h"
#include "File\File.h"
#include "JobSystem\JobSystem.h"
#include "Colliders\ColliderManager.h"
#include "GameObject\GameObjectManager.h"
#include "Render\RenderManager.h"

namespace Engine
{

	class ZEngine
	{

	private:
		static ZEngine* m_Instance;
		

	public:
		bool bQuit;
		
		ZEngine();
		~ZEngine();

		void Init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
		void Run();
		void Shutdown();

		static ZEngine* Instance();
		
	};


}
