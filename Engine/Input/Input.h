#pragma once

#include <stdio.h>
#include <unordered_map>
#include "DebugTool\Debug.h"
#include "Base\Singleton.h"

namespace Engine
{
	class Input : public Singleton<Input>
	{
	private:
		static Input* m_Instance;
		std::unordered_map<int, bool> m_KeyStates;

	public:
		Input();
		~Input();

		//For engine loop
		void Init();
		void Shutdown();

		//temp state flag
		bool IsKeyDown(int i_KeyID);
		bool isKeyUp(int i_KeyID);

		//Get key input
		static void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);

		void UpdateKeyState(unsigned int i_VKeyID, bool bWentDown);
	};
		
}