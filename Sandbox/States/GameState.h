#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>

#include "../../states/State.h"

class GameState : public vtx::State
{

public:
	void Init()
	{
		std::cout << "Created GameState" << std::endl;
	}

	void Cleanup()
	{

	}

	void Pause()
	{

	}

	void Resume()
	{

	}

	void FixedUpdate()
	{
		
	}

	void VariableUpdate(float delta)
	{
		
	}

	void Draw()
	{

	}

	static GameState* Instance()
	{
		if (instance == 0)
			instance = new GameState();

		return instance;
	}

private:
	static GameState* instance;
	GameState() { }
};

GameState* GameState::instance = nullptr;

#endif
