#include "Controller.h"

namespace Engine {

	Controller::Controller()
	{
		sprite = nullptr;
	}

	Controller::~Controller()
	{
		delete sprite;
	}

}