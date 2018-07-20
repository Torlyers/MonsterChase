#pragma once
#include<stdio.h>
#include "GameObject\Controller.h"

namespace Engine {

	class GameObjectController : public Controller
	{
	private:		

	public:

		void move() override;
		virtual void move(char input);
		virtual void move(Vector2 aim);
		
		GameObjectController();
		GameObjectController(GameObject* i_GameObject);
		~GameObjectController();


	};

}