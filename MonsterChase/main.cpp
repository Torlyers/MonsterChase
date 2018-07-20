#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <list>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"
#include "File\File.h"
#include "Game.h"
#include "Engine\Engine.h"
#include "DebugTool\Debug.h"
#include "Input\Input.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	Engine::Engine* engine = Engine::Engine::Instance();
	
	Game* game = Game::Instance();

	GLib::SetKeyStateChangeCallback(Engine::Input::Instance()->TestKeyCallback);

	engine->Init(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);
	game->Init();	
	
	bool bQuit = false;

	do //every frame
	{
		engine->Run();
		game->Run();

	} while (engine->bQuit == false);

	game->Shutdown();
	engine->Shutdown();

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}
