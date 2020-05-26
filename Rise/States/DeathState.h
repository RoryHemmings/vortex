#pragma once

#ifndef SANDBOX_DEATH_STATE_H
#define SANDBOX_DEATH_STATE_H

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

#include "../../states/State.h"
#include "../../core/Application.h"

#include "../../util/Math.h"

#include "../Scripts/Block.h"

class DeathState : public vtx::State
{

public:
	DeathState(vtx::Application* app);

	void Load();
	void Unload() { entityCoordinator.Clear(); }
	void Pause() { }
	void Resume() { }

	void FixedUpdate();
	void VariableUpdate(float d) { }
	void Draw();

private:
	sf::Font font;
	sf::Text text;

};

#endif