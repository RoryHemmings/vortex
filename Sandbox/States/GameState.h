#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>

#include "../../states/State.h"

class GameState : public vtx::State
{

public:
	void Init(vtx::Application* app)
	{
		std::cout << "Created GameState" << std::endl;
		tree = sf::Sprite();
		tree.setTexture(app->GetAssetHolder().textures.Get("Abe"));
		tree.scale(sf::Vector2f(10, 10));
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
		sf::Vector2f pos(tree.getPosition());
		tree.setPosition(sf::Vector2f(pos.x + 0.001f, pos.y));
	}

	void VariableUpdate(vtx::Application* app, float delta)
	{
		std::cout << 1/delta << std::endl;
	}

	void Draw(vtx::Application* app)
	{
		app->GetRenderWindow().draw(tree);
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

	sf::Sprite tree;
};

GameState* GameState::instance = nullptr;

#endif
