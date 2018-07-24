#include "Engine.h"
#include "Profiling/Profiler.h"
#include "Message/MessageManager.h"



namespace Engine {

	ZEngine::ZEngine()
	{
		bQuit = false;
	}

	ZEngine::~ZEngine()
	{

	}

	void ZEngine::Init(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
	{
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Pong", -1, 800, 450);
		
		if (bSuccess)
		{
			JobSystem::Init();
			GameObjectManager::Instance()->Init();
			Input::Instance()->Init();			
			TimeManager::Instance()->Init();
			ColliderManager::Instance()->Init();
			PhysicsManager::Instance()->Init();
			RenderManager::Instance()->Init();
			Profiler::Instance()->Init();
			MessageManager::Instance()->Init();
		}
	}

	void ZEngine::Run()
	{
		
		GLib::Service(bQuit);

		GameObjectManager::Instance()->Run();
		TimeManager::Instance()->Update();
		ColliderManager::Instance()->Run();
		PhysicsManager::Instance()->Run(TimeManager::Instance()->GetFrameDeltaTime());
		RenderManager::Instance()->Run();
		
	}

	void ZEngine::Shutdown()
	{
		Profiler::Instance()->OutputProfile();
		GameObjectManager::Instance()->ShutDown();		
		RenderManager::Instance()->ShutDown();
		TimeManager::Instance()->Shutdown();
		PhysicsManager::Instance()->Shutdown();
		Input::Instance()->Shutdown();
		ColliderManager::Instance()->Shutdown();
		Profiler::Instance()->Shutdown();
		MessageManager::Instance()->ShutDown();

		JobSystem::Shutdown();
	}
}