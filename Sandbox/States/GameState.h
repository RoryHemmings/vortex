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

		circle = sf::CircleShape(50.0f);
		circle.setFillColor(sf::Color(100, 250, 50));
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

	void FixedUpdate(vtx::Application* app)
	{
		
	}

	void VariableUpdate(vtx::Application* app, float delta)
	{
		
	}

	void Draw(vtx::Application* app)
	{
		app->GetRenderWindow().draw(circle);
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

	sf::CircleShape circle;
};

GameState* GameState::instance = nullptr;

#endif
