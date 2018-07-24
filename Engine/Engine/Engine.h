#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <memory>

#include "GameObject\GameObject.h"
#include "Time\TimeManager.h"
#include "Physics\PhysicsManager.h"
#include "Input\Input.h"
#include "File\File.h"
#include "JobSystem\JobSystem.h"
#include "Colliders\ColliderManager.h"
#include "GameObject\GameObjectManager.h"
#include "Render\RenderManager.h"
#include "Base\Singleton.h"

using namespace std;

namespace Engine
{
	class ZEngine : public Singleton<ZEngine>
	{
	private:

	public:
		bool bQuit;
		
		ZEngine();
		~ZEngine();

		void Init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
		void Run();
		void Shutdown();
		
	};
}