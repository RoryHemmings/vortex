#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>

#include "../../states/State.h"

#include "../../util/Math.h"

class GameState : public vtx::State
{

public:
	GameState(vtx::Application* app)
		: State(app)
	{ }

	/*
		User defines systemsa nd which entities/components are utilized
	*/
	void Load()
	{
		entityCoordinator.Init();

		entityCoordinator.RegisterComponent<vtx::components::Transfrom>();
		entityCoordinator.RegisterComponent<vtx::components::Renderer>();

		entityCoordinator.RegisterSystem<vtx::systems::RenderSystem>();

		vtx::Signature signature;
		signature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
		signature.set(entityCoordinator.GetComponentType<vtx::components::Renderer>());
		entityCoordinator.SetSystemSignature<vtx::systems::RenderSystem>(signature);

		vtx::Entity player = entityCoordinator.CreateEntity();
		entityCoordinator.AddComponent(
			player,
			vtx::components::Transfrom{ vtx::Vec2f(100, 100), 0.0, {1.0, 1.0} });
		entityCoordinator.AddComponent(
			player,
			vtx::components::Renderer{ app->GetAssetHolder().textures.Get("john") });
	}

	void Unload()
	{
		entityCoordinator.Clear();
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
		entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->Draw(app, &entityCoordinator);
	}

private:
	

};

#endif
