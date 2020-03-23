#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>

#include "../Entities/Player.h"
#include "../../states/State.h"

class GameState : public vtx::State
{

public:
	GameState(vtx::Application* app)
		: State(app)
		, player(app, 100, 100)
	{
		
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
		player.FixedUpdate();
	}

	void VariableUpdate(float delta)
	{
		player.VariableUpdate(delta);
	}

	void Draw()
	{
		player.Draw();
	}

private:
	Player player;

};

#endif
