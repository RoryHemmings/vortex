#pragma once

#include <string>

#include "../core/Application.h"

#include "States/States.h"

class Game : public vtx::Application
{

public:
	Game(const std::string& title, int width, int height, float fixedUpdateRate) 
		: Application(title, width, height, fixedUpdateRate) { }

private:

	void init()
	{
		ChangeState(States::GAME_STATE);

		initWindow();
	}

	void cleanup()
	{

	}

};

