#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<list>
#include<unordered_map>

#include"Header.h"
#include"Engine\Engine.h"
#include "GameObject\GameObject.h"
#include "SmartPointer\SharedPointer.h"

enum GameState
{
	Start,
	ServeBall,
	Battle,
	GameOver,
};


class Game
{
private:
	
	static Game* m_Instance;
	void AddGameObjectFromLua(std::string i_Name, const char* i_FilePath);
	std::unordered_map<int, const char*> IndexPath;
	
	int PlayerScore1;
	int PlayerScore2;

public:	

	Game();
	~Game();
	void Init();
	void Run();	
	void Shutdown();	

	bool newball;
	GameState state;

	void CheckInput();
	void CheckBallPosition();
	void CheckGameOver();
	void ResetBall();
	void UpdateScore1(int score);
	void UpdateScore2(int score);

	static Game* Instance();
};