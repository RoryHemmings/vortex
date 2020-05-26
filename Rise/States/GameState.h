#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../../states/State.h"
#include "../../core/Application.h"

#include "../../util/Math.h"

#include "../Scripts/Block.h"

class GameState : public vtx::State
{

public:
	GameState(vtx::Application* app);

	void Load();
	void Unload();
	void Pause() { }
	void Resume() { }

	void FixedUpdate();
	void VariableUpdate(float d) { delta = d; }
	void Draw();

private:
	void initAssets();
	void initPlayer();
	void SetBlockCombos();
	void initObstacles();

	void controlPlayer();
	bool controlObstacles();

	void die();

	//vtx::Entity createBeam(float x, float y, float friction = 0.3f);
	Block createBlock(float x);

	// Entities
	vtx::Entity player;
	std::vector<std::vector<ObstacleInfo>> blockCombos;
	std::vector<Block> blocks;

	// Assets
	sf::Texture playerTexture1;
	sf::Texture playerTexture2;
	sf::Texture short_beam;
	sf::Texture long_beam;
	sf::Texture empty;
	sf::Texture buildings[5];
	sf::Font font;

	// Shortcuts
	std::shared_ptr<vtx::systems::RenderSystem> renderSystem;
	std::shared_ptr<vtx::systems::PhysicsSystem> physicsSystem;

	// Misc.
	sf::Text fpsMeter;
	sf::Text drawnEntities;
	float delta;

	int blockNum;

};

#endif
