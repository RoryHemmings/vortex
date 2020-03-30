#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>

#include "../Entities/Player.h"

#include "../../entities/EntityManager.h"
#include "../../states/State.h"

class GameState : public vtx::State, public vtx::EntityManager
{

public:
	GameState(vtx::Application* app)
		: State(app)
		, EntityManager(app)
	{
		Player player(app, 100, 100);
		AddEntity(player, "player");

		

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
		vtx::EntityManager::FixedUpdate();
	}

	void VariableUpdate(float delta)
	{
		vtx::EntityManager::VariableUpdate(delta);
	}

	void Draw()
	{
		vtx::EntityManager::Draw();
	}

private:
	

};

#endif
