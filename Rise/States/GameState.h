#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <list>

#include "../../states/State.h"
#include "../../core/Application.h"

#include "../../util/Math.h"

class GameState : public vtx::State
{

public:
	GameState(vtx::Application* app);

	void Load();
	void Unload() { entityCoordinator.Clear(); }
	void Pause() { }
	void Resume() { }

	void FixedUpdate();
	void VariableUpdate(float d) { delta = d; }
	void Draw();

private:
	void initAssets();
	void initPlayer();
	void initFloor();
	void initObstacles();

	void controlPlayer();
	void controlObstacles();

	vtx::Entity createBeam(float x, float y, float friction = 0.3f);

	sf::Text fpsMeter;
	sf::Text drawnEntities;

	sf::Font font;
	float delta;

	vtx::Entity player;
	std::list<vtx::Entity> obstacles;

	sf::Texture playerTexture1;
	sf::Texture playerTexture2;
	sf::Texture beam;
	sf::Texture empty;

};

#endif
