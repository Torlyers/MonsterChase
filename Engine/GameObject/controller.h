#pragma once
#include<stdio.h>
#include "Math/Vector2.h"
#include "GameObject/GameObject.h"
#include "Header.h"

namespace Engine {

	class Controller
	{
	public:

		friend class GameObject;

		GameObject* sprite;

		enum Dierction
		{
			UP, DOWN, LEFT, RIGHT
		};

		Controller();
		virtual ~Controller();

		virtual void move() = 0;
		virtual void move(char input) = 0;
		virtual void move(Vector2 aim) = 0;
	};

}