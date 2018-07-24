
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
		if (Game::Instance()->state == GameState::Start)
		{
			Game::Instance()->text->SetPosition(0.0f, 1000.0f);
			Game::Instance()->ball->GetRigidBody()->SetVelocity(Vector2(100.0f, 100.0f));
			Game::Instance()->state = GameState::Battle;
		}
		else if (Game::Instance()->state == GameState::ServeBall)
		{
			Game::Instance()->ball->GetRigidBody()->SetVelocity(Vector2(100.0f, 100.0f));
			Game::Instance()->state = GameState::Battle;
		}
		else if (Game::Instance()->state == GameState::GameOver)
		{
			ZEngine::Instance()->bQuit = true;
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

	ball = GameObjectMgr->CreateGameObjectFromLua("Data\\ball.lua");
	text = GameObjectMgr->CreateGameObjectFromLua("Data\\text.lua");
	gameover = GameObjectMgr->CreateGameObjectFromLua("Data\\gameover.lua");
	score1 = GameObjectMgr->CreateGameObjectFromLua("Data\\score1.lua");
	score2 = GameObjectMgr->CreateGameObjectFromLua("Data\\score2.lua");
	player1 = GameObjectMgr->CreateGameObjectFromLua("Data\\pat.lua");
	player2 = GameObjectMgr->CreateGameObjectFromLua("Data\\pat1.lua");
	bg = GameObjectMgr->CreateGameObjectFromLua("Data\\bg.lua");
	wallup = GameObjectMgr->CreateGameObjectFromLua("Data\\wallup.lua");
	wallbottom = GameObjectMgr->CreateGameObjectFromLua("Data\\wallbottom.lua");

}

Game::~Game()
{
	
}

SpacePressedReceiver* receiver;

void Game::Init()
{
	receiver = new SpacePressedReceiver();
	Delegate<> tempDelegate = Delegate<>::Create<SpacePressedReceiver, &SpacePressedReceiver::OnSpacePressed>(receiver);
	MessageManager::Instance()->AddDelegate("PRESSED_32", tempDelegate);
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
	JobSystem::IJob* p_LoadGo = new JobSystem::IJobLoadGameObjectFile(i_Name, i_FilePath);
	ASSERT(p_LoadGo);
	JobSystem::RunJob(p_LoadGo, "LoadFile");
}

void Game::CheckBallPosition()
{
	if (state == GameState::Battle)
	{
		float posx = ball->GetPosition().x();
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
		if (Input::Instance()->IsKeyDown(87))//p1 up
		{
			player1->GetRigidBody()->AddForce(Vector2(0.0f, 10000.0f));
		}
		else if (Input::Instance()->IsKeyDown(83))//p1 down
		{
			player1->GetRigidBody()->AddForce(Vector2(0.0f, -10000.0f));
		}

		if (Input::Instance()->IsKeyDown(73))//p2 up
		{
			player2->GetRigidBody()->AddForce(Vector2(0.0f, 10000.0f));
		}
		else if (Input::Instance()->IsKeyDown(75))//p2 down
		{
			player2->GetRigidBody()->AddForce(Vector2(0.0f, -10000.0f));
		}
	}
}

void Game::CheckGameOver()
{
	if (PlayerScore1 >= 5 || PlayerScore2 >= 5)
	{
		state = GameState::GameOver;
		gameover->SetPosition(Vector2(0.0f, 0.0f));
	}
}

void Game::UpdateScore1(int score)
{
	score1->GetRenderer()->ShutDown();
	GLib::Sprites::Sprite* sprite = RenderManager::Instance()->CreateSprite(IndexPath[score]);
	score1->GetRenderer()->SetSprite(sprite);	
}

void Game::UpdateScore2(int score)
{
	score2->GetRenderer()->ShutDown();
	GLib::Sprites::Sprite* sprite = RenderManager::Instance()->CreateSprite(IndexPath[score]);
	score2->GetRenderer()->SetSprite(sprite);
}

void Game::ResetBall()
{
	state = GameState::ServeBall;
	ball->GetRigidBody()->SetVelocity(Vector2(0.0f, 0.0f));
	ball->SetPosition(Vector2(0.0f, 0.0f));
}