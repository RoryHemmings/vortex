#include "DeathState.h"

#include "../../util/Math.h"
#include "../../States/States.h"

#include "GameState.h"

DeathState::DeathState(vtx::Application* app)
	: State(app)
{
	font.loadFromFile("Consolas.ttf");

	text.setPosition(app->GetWidth() / 4, app->GetHeight() / 3);
	text.setCharacterSize(68);
	text.setFont(font);

	text.setString("You Died, press R to respawn");
}

void DeathState::Load()
{
	entityCoordinator.Init();

	entityCoordinator.RegisterComponent<vtx::components::Transfrom>();
	entityCoordinator.RegisterComponent<vtx::components::Renderer>();
	entityCoordinator.RegisterComponent<vtx::components::Physics>();

	entityCoordinator.RegisterSystem<vtx::systems::RenderSystem>(app, 60);	// 60 is pixel to meter ratio
	entityCoordinator.RegisterSystem<vtx::systems::PhysicsSystem>(app, 60); // 60 is gravity in meters per second^2

	vtx::Signature rsSignature;

	rsSignature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
	rsSignature.set(entityCoordinator.GetComponentType<vtx::components::Renderer>());
	entityCoordinator.SetSystemSignature<vtx::systems::RenderSystem>(rsSignature);

	vtx::Signature psSignature;
	psSignature.set(entityCoordinator.GetComponentType<vtx::components::Transfrom>());
	psSignature.set(entityCoordinator.GetComponentType<vtx::components::Physics>());
	entityCoordinator.SetSystemSignature<vtx::systems::PhysicsSystem>(psSignature);
}

void DeathState::FixedUpdate()
{
	if (vtx::InputManager::KeyIsPressed(vtx_key::R)) {
		vtx::States::RemoveState("GameState");
		vtx::States::AddState(new GameState(app), "GameState");
		vtx::States::SetCurrentState("GameState");
	}
}

void DeathState::Draw()
{
	entityCoordinator.GetSystem<vtx::systems::RenderSystem>()->Draw();

	app->GetRenderWindow().draw(text);
}
