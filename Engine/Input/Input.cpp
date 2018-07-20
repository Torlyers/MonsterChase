#include "Input.h"
#include "Message/MessageManager.h"

namespace Engine {	

	Input* Input::m_Instance = nullptr;

	Input* Input::Instance()
	{
		if (!m_Instance)
			m_Instance = new Input();
		return m_Instance;
	}

	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	void Input::Init()
	{
		m_KeyStates[32] = false;
		m_KeyStates[87] = false;
		m_KeyStates[83] = false;
		m_KeyStates[73] = false;
		m_KeyStates[75] = false;
	}

	void Input::Shutdown()
	{
		if(m_Instance != nullptr)
			delete m_Instance;
	}

	void Input::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
	{
		bool LastState = Instance()->m_KeyStates[i_VKeyID];
		if (LastState && !bWentDown)//released
		{			
			Instance()->m_KeyStates[i_VKeyID] = bWentDown;
		}
		else if (!LastState && bWentDown)//pressed
		{			
			if(i_VKeyID == 32)
				MessageManager::Instance()->BroadCastMessage("PRESSED_32");
			Instance()->m_KeyStates[i_VKeyID] = bWentDown;
		}
	}

	bool Input::IsKeyDown(int i_KeyID)
	{
		return m_KeyStates[i_KeyID];
	}

	bool Input::isKeyUp(int i_KeyID)
	{
		return !m_KeyStates[i_KeyID];
	}
}