#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>
#include <string>

#include "../../states/State.h"

#include "../../util/Math.h"

class GameState : public vtx::State
{

public:
	GameState(vtx::Application* app)
		: State(app)
	{
		font.loadFromFile("Consolas.ttf");

		text.setPosition(app->GetWidth() - 135, 20);
		text.setCharacterSize(14);
		text.setFont(font);
	}

	/*
		User defines systems and which entities/components are utilized
	*/
	void Load()
	{
		entityCoordinator.Init();

		entityCoordinator.RegisterComponent<vtx::components::Transfrom>();
		entityCoordinator.RegisterComponent<vtx::components::Renderer>();
		entityCoordinator.RegisterComponent<vtx::components::Physics>();

		entityCoordinator.RegisterSystem<vtx::systems::RenderSystem>();
		entityCoordinator.RegisterSystem<vtx::systems::PhysicsSystem>();

		vtx::Signature rsSignature;
		rsSignature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
		rsSignature.set(entityCoordinator.GetComponentType<vtx::components::Renderer>());
		entityCoordinator.SetSystemSignature<vtx::systems::RenderSystem>(rsSignature);

		vtx::Signature psSignature;
		psSignature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
		psSignature.set(entityCoordinator.GetComponentType<vtx::components::Physics>());
		entityCoordinator.SetSystemSignature<vtx::systems::PhysicsSystem>(psSignature);

		vtx::Entity player = entityCoordinator.CreateEntity();
		entityCoordinator.AddComponent(
			player,
			vtx::components::Transfrom{ vtx::Vec2f(100, 100), 0.0, {1.0, 1.0} });
		entityCoordinator.AddComponent(
			player,
			vtx::components::Renderer{ app->GetAssetHolder().textures.Get("john") });
		entityCoordinator.AddComponent(
			player,
			vtx::components::Physics{});
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
		entityCoordinator.GetSystem<vtx::systems::PhysicsSystem>()->FixedUpdate(app, &entityCoordinator);
	}

	void VariableUpdate(float d)
	{
		delta = d;
	}

	void Draw()
	{
		entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->Draw(app, &entityCoordinator);

		text.setString("fps: " + std::to_string(1.0f / delta));
		app->GetRenderWindow().draw(text);
	}

private:
	sf::Text text;
	sf::Font font;
	float delta;

};

#endif
