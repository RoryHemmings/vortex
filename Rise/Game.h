#pragma once

#include <string>

#include "../core/Application.h"
#include "../States/States.h"

#include "States/GameState.h"

class Game : public vtx::Application
{

public:
	Game(const std::string& title, int width, int height, float fixedUpdateRate, const std::string& assetFolder)
		: Application(title, width, height, fixedUpdateRate, assetFolder) { }

private:

	void init()
	{
		vtx::States::AddState(new GameState(this), "GameState");
		vtx::States::SetCurrentState("GameState");

		initWindow();
	}

	void cleanup()
	{
		// Cleanup states
		vtx::States::GetCurrentState().Unload();
	}

};

