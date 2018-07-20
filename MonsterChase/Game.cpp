
#include"Game.h"
#include"Debugtool/Debug.h"
#include"JobSystem/JobSystem.h"
#include "JobSystem/IJob.h"
#include "JobSystem/Jobs/IJobLoadGameObjectFile.h"
#include "Message/Delegate.h"
#include "Message/MessageManager.h"
#include "GameObject/GameObjectManager.h"
#include "Math/Vector2.h"
#include "Render/RenderManager.h"

class SpacePressedReceiver
{
public:
	void OnSpacePressed()
	{
		auto map = Engine::GameObjectManager::Instance()->GameObjects;
		if (Game::Instance()->state == GameState::Start)
		{
			map["text"]->SetPosition(0.0f, 1000.0f);
			map["ball"]->GetRigidBody()->SetVelocity(Engine::Vector2(100.0f, 100.0f));
			Game::Instance()->state = GameState::Battle;
		}
		else if (Game::Instance()->state == GameState::ServeBall)
		{
			map["ball"]->GetRigidBody()->SetVelocity(Engine::Vector2(100.0f, 100.0f));
			Game::Instance()->state = GameState::Battle;
		}
		else if (Game::Instance()->state == GameState::GameOver)
		{
			Engine::Engine::Instance()->bQuit = true;
		}
	}
};

Game* Game::m_Instance = nullptr;

Game* Game::Instance()
{
	if (!m_Instance)
		m_Instance = new Game();
	return m_Instance;
}

Game::Game()
{
	newball = false;
	state = GameState::Start;
	PlayerScore1 = 0;
	PlayerScore2 = 0;

	IndexPath[1] = "Data\\1.dds";
	IndexPath[2] = "Data\\2.dds";
	IndexPath[3] = "Data\\3.dds";
	IndexPath[4] = "Data\\4.dds";
	IndexPath[5] = "Data\\5.dds";

}

Game::~Game()
{
	
}

SpacePressedReceiver* receiver;

void Game::Init()
{
	receiver = new SpacePressedReceiver();
	Engine::Delegate<> tempDelegate = Engine::Delegate<>::Create<SpacePressedReceiver, &SpacePressedReceiver::OnSpacePressed>(receiver);
	Engine::MessageManager::Instance()->AddDelegate("PRESSED_32", tempDelegate);
	
	Engine::JobSystem::CreateQueue("LoadFile", 1);
	Engine::JobSystem::CreateQueue("CreateGameObject", 1);
	
	AddGameObjectFromLua("text", "Data\\text.lua");
	AddGameObjectFromLua("gameover", "Data\\gameover.lua");
	AddGameObjectFromLua("ball", "Data\\ball.lua");
	AddGameObjectFromLua("score1", "Data\\score1.lua");
	AddGameObjectFromLua("score2", "Data\\score2.lua");
	AddGameObjectFromLua("player1", "Data\\pat.lua");
	AddGameObjectFromLua("player2", "Data\\pat1.lua");
	AddGameObjectFromLua("bg", "Data\\bg.lua");
	AddGameObjectFromLua("wallup", "Data\\wallup.lua");
	AddGameObjectFromLua("wallbottom", "Data\\wallbottom.lua");
}

void Game::Run()
{
	CheckInput();
	CheckBallPosition();
	CheckGameOver();
}


void Game::Shutdown()
{
	delete receiver;

	if(m_Instance != nullptr)
		delete m_Instance;
}

void Game::AddGameObjectFromLua(std::string i_Name, const char* i_FilePath)
{
	Engine::JobSystem::IJob* p_LoadGo = new Engine::JobSystem::IJobLoadGameObjectFile(i_Name, i_FilePath);
	ASSERT(p_LoadGo);
	Engine::JobSystem::RunJob(p_LoadGo, "LoadFile");
}

void Game::CheckBallPosition()
{
	if (state == GameState::Battle)
	{
		auto map = Engine::GameObjectManager::Instance()->GameObjects;
		float posx = map["ball"]->GetPosition().x();
		if (posx < -500.0f)
		{
			UpdateScore2(++PlayerScore2);
			ResetBall();
		}
		else if (posx > 500.0f)
		{
			UpdateScore1(++PlayerScore1);
			ResetBall();
		}
	}
}

void Game::CheckInput()
{
	if (state == GameState::Battle)
	{
		auto map = Engine::GameObjectManager::Instance()->GameObjects;

		if (Engine::Input::Instance()->IsKeyDown(87))//p1 up
		{
			map["player1"]->GetRigidBody()->AddForce(Engine::Vector2(0.0f, 10000.0f));
		}
		else if (Engine::Input::Instance()->IsKeyDown(83))//p1 down
		{
			map["player1"]->GetRigidBody()->AddForce(Engine::Vector2(0.0f, -10000.0f));
		}

		if (Engine::Input::Instance()->IsKeyDown(73))//p2 up
		{
			map["player2"]->GetRigidBody()->AddForce(Engine::Vector2(0.0f, 10000.0f));
		}
		else if (Engine::Input::Instance()->IsKeyDown(75))//p2 down
		{
			map["player2"]->GetRigidBody()->AddForce(Engine::Vector2(0.0f, -10000.0f));
		}
	}
}

void Game::CheckGameOver()
{
	if (PlayerScore1 >= 5 || PlayerScore2 >= 5)
	{
		auto map = Engine::GameObjectManager::Instance()->GameObjects;
		state = GameState::GameOver;
		map["gameover"]->SetPosition(Engine::Vector2(0.0f, 0.0f));
	}
}

void Game::UpdateScore1(int score)
{
	auto map = Engine::GameObjectManager::Instance()->GameObjects;
	map["score1"]->GetRenderer()->ShutDown();
	GLib::Sprites::Sprite* sprite = Engine::RenderManager::Instance()->CreateSprite(IndexPath[score]);
	map["score1"]->GetRenderer()->SetSprite(sprite);	
}

void Game::UpdateScore2(int score)
{
	auto map = Engine::GameObjectManager::Instance()->GameObjects;
	map["score2"]->GetRenderer()->ShutDown();
	GLib::Sprites::Sprite* sprite = Engine::RenderManager::Instance()->CreateSprite(IndexPath[score]);
	map["score2"]->GetRenderer()->SetSprite(sprite);
}

void Game::ResetBall()
{
	state = GameState::ServeBall;
	auto map = Engine::GameObjectManager::Instance()->GameObjects;
	map["ball"]->GetRigidBody()->SetVelocity(Engine::Vector2(0.0f, 0.0f));
	map["ball"]->SetPosition(Engine::Vector2(0.0f, 0.0f));
}