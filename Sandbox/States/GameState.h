#pragma once

#ifndef SANDBOX_GAME_STATE_H
#define SANDBOX_GAME_STATE_H

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

#include "../../states/State.h"

#include "../../util/Math.h"

class GameState : public vtx::State
{

public:
	GameState(vtx::Application* app)
		: State(app), delta(0)
	{
		font.loadFromFile("Consolas.ttf");

		fpsMeter.setPosition(app->GetWidth() - 135, 20);
		fpsMeter.setCharacterSize(14);
		fpsMeter.setFont(font);

		drawnEntities.setPosition(app->GetWidth() - 135, 50);
		drawnEntities.setCharacterSize(14);
		drawnEntities.setFont(font);
	}

	/*
		User defines systems and which entities/components are utilized

		User must define ECS objects in this order
			1. Components
			2. Systems
			3. Entities
	*/
	void Load()
	{
		entityCoordinator.Init();

		entityCoordinator.RegisterComponent<vtx::components::Transfrom>();
		entityCoordinator.RegisterComponent<vtx::components::Renderer>();
		entityCoordinator.RegisterComponent<vtx::components::Physics>();

		entityCoordinator.RegisterSystem<vtx::systems::RenderSystem>(app, 60);	// 60 is pixel to meter ratio
		entityCoordinator.RegisterSystem<vtx::systems::PhysicsSystem>(app, 60); // 30 is gravity in meters per second

		vtx::Signature rsSignature;
		
		rsSignature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
		rsSignature.set(entityCoordinator.GetComponentType<vtx::components::Renderer>());
		entityCoordinator.SetSystemSignature<vtx::systems::RenderSystem>(rsSignature);

		vtx::Signature psSignature;
		psSignature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
		psSignature.set(entityCoordinator.GetComponentType<vtx::components::Physics>());
		entityCoordinator.SetSystemSignature<vtx::systems::PhysicsSystem>(psSignature);

		initAssets();
		initPlayer();

		CreateStaticRectangle(0, 9.8, app->GetWidth(), 50);
		CreateBeam(5, 7);
	}

	void Unload()
	{
		entityCoordinator.Clear();
	}

	void Pause()
	{ }

	void Resume()
	{ }

	void FixedUpdate()
	{

		entityCoordinator.GetSystem<vtx::systems::PhysicsSystem>()->FixedUpdate();
		controlPlayer();
		
		entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->FixedUpdate();

		fpsMeter.setString("fps: " + std::to_string(1.0f / delta));
		drawnEntities.setString("neos: " + std::to_string(entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->GetNumEntitiesRendered()));
	}

	void VariableUpdate(float d)
	{
		delta = d;
	}

	void Draw()
	{
		entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->Draw();
		//std::cout << entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->entities.size() << std::endl;
		//std::cout << entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->GetNumEntitiesRendered() << std::endl;

		app->GetRenderWindow().draw(fpsMeter);
		app->GetRenderWindow().draw(drawnEntities);
	}

private:
	void initAssets()
	{
		playerTexture1 = app->GetAssetHolder().textures.Get("John1");
		playerTexture2 = app->GetAssetHolder().textures.Get("John2");
		beam = app->GetAssetHolder().textures.Get("beam");

		empty = app->GetAssetHolder().textures.Get("null");
	}

	void controlPlayer()
	{
		auto& physics = entityCoordinator.GetComponent<vtx::components::Physics>(player);
		auto& body = entityCoordinator.GetComponent<vtx::components::Physics>(player).body;
		auto& renderer = entityCoordinator.GetComponent <vtx::components::Renderer>(player);

		float moveX = 0.0f;
		float speed = 10.0f;

		if (vtx::InputManager::KeyIsPressed(vtx_key::D)) {
			moveX = speed;
			renderer.SetAnimation("walking", 10.0f);
		}
		if (vtx::InputManager::KeyIsPressed(vtx_key::A)) {
			moveX = -speed;
			renderer.SetAnimation("walking", 10.0f, true);
		}
		if (moveX == 0) renderer.SetAnimation("static", 0.0f, renderer.flipX);

		if (vtx::InputManager::KeyIsPressed(vtx_key::Space) && physics.bottomTouching)
			body->ApplyLinearImpulseToCenter({0, body->GetMass() * -7.0f}, true);

		body->SetLinearVelocity({ moveX, body->GetLinearVelocity().y });
	}

	void initPlayer()
	{
		player = entityCoordinator.CreateEntity();

		vtx::components::Transfrom transform;
		transform.position = vtx::Vec2f(10, 0);
		transform.scale.x = entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(playerTexture1.getSize().x);
		transform.scale.y = entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(playerTexture1.getSize().y);

		vtx::components::Physics physics;
		physics.friction = 0.001f;
		physics.density = 1.0f;

		vtx::components::Renderer renderer;
		renderer.AddAnimation("static", { &playerTexture1 });
		renderer.AddAnimation("walking", { &playerTexture1, &playerTexture2 });
		renderer.SetAnimation("static");

		entityCoordinator.AddComponent(player, transform);
		entityCoordinator.AddComponent(player, renderer);
		entityCoordinator.AddComponent(player, physics);
	}

	void CreateBeam(float x, float y, float friction = 0.3f)
	{
		vtx::Entity box = entityCoordinator.CreateEntity();

		vtx::components::Transfrom transform;
		transform.position = vtx::Vec2f(x, y);
		transform.scale.x = entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(beam.getSize().x);
		transform.scale.y = entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(beam.getSize().y);

		vtx::components::Physics physics;
		physics.friction = friction;
		physics.type = b2_staticBody;

		vtx::components::Renderer renderer;
		renderer.AddAnimation("static", { &beam });
		renderer.SetAnimation("static");

		entityCoordinator.AddComponent(box, transform);
		entityCoordinator.AddComponent(box, renderer);
		entityCoordinator.AddComponent(box, physics);
	}

	void CreateStaticRectangle(float x, float y, float width, float height, float friction=0.3f)
	{
		vtx::Entity box = entityCoordinator.CreateEntity();

		vtx::components::Transfrom transform;
		transform.position = vtx::Vec2f(x, y);
		transform.scale.x = entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(width);
		transform.scale.y = entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(height);

		vtx::components::Physics physics;
		physics.friction = friction;
		physics.type = b2_staticBody;

		vtx::components::Renderer renderer;
		renderer.AddAnimation("static", { &empty });
		renderer.SetAnimation("static");

		entityCoordinator.AddComponent(box, transform);
		entityCoordinator.AddComponent(box, renderer);
		entityCoordinator.AddComponent(box, physics);
	}

	sf::Text fpsMeter;
	sf::Text drawnEntities;

	sf::Font font;
	float delta;

	vtx::Entity player;
	sf::Texture playerTexture1;
	sf::Texture playerTexture2;
	sf::Texture beam;
	sf::Texture empty;

};

#endif
