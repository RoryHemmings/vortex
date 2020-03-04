#pragma once

#include <string>

#include "../core/Application.h"

#include "States/States.h"

class Game : public vtx::Application
{

public:
	Game(const std::string& title, int width, int height, float fixedUpdateRate, const std::string& assetFolder)
		: Application(title, width, height, fixedUpdateRate, assetFolder) { }

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

