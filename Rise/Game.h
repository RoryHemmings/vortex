#pragma once

#ifndef GAME_H
#define GAME_H

#include <string>

#include "../core/Application.h"
#include "../States/States.h"

#include "States/GameState.h"
#include "States/DeathState.h"

class Game : public vtx::Application
{

public:
	Game(const std::string& title, int width, int height, float fixedUpdateRate, const std::string& assetFolder)
		: Application(title, width, height, fixedUpdateRate, assetFolder) { }

private:

	void init()
	{
		vtx::States::AddState(new GameState(this), "GameState");
		vtx::States::AddState(new DeathState(this), "DeathState");

		vtx::States::SetCurrentState("GameState");

		initWindow();
	}

	void cleanup()
	{
		// Cleanup states
		vtx::States::GetCurrentState().Unload();
	}

};

#endif
