#include "GameState.h"

#include "../../util/Math.h"
#include "../../States/States.h"

GameState::GameState(vtx::Application* app)
	: State(app), delta(0), blockNum(0)
{
	font.loadFromFile("Consolas.ttf");

	fpsMeter.setPosition(app->GetWidth() - 135, 20);
	fpsMeter.setCharacterSize(14);
	fpsMeter.setFont(font);

	drawnEntities.setPosition(app->GetWidth() - 135, 50);
	drawnEntities.setCharacterSize(14);
	drawnEntities.setFont(font);
}

void GameState::Load()
{
	entityCoordinator.Init();

	entityCoordinator.RegisterComponent<vtx::components::Transfrom>();
	entityCoordinator.RegisterComponent<vtx::components::Renderer>();
	entityCoordinator.RegisterComponent<vtx::components::Physics>();

	renderSystem = entityCoordinator.RegisterSystem<vtx::systems::RenderSystem>(app, 60);	// 60 is pixel to meter ratio
	physicsSystem = entityCoordinator.RegisterSystem<vtx::systems::PhysicsSystem>(app, 60); // 60 is gravity in meters per second^2

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
	initObstacles();
}

void GameState::Unload()
{
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i].ClearEntities();
	}

	entityCoordinator.Clear();
}

void GameState::FixedUpdate()
{
	entityCoordinator.GetSystem<vtx::systems::PhysicsSystem>()->FixedUpdate();

	controlPlayer();
	if (!controlObstacles()) return;

	renderSystem->FixedUpdate();

	fpsMeter.setString("fps: " + std::to_string(1.0f / delta));
	drawnEntities.setString("Entities: " + std::to_string(renderSystem->GetNumEntitiesRendered()));
}

void GameState::Draw()
{
	renderSystem->Draw();
	//std::cout << renderSystem->entities.size() << std::endl;
	//std::cout << renderSystem->GetNumEntitiesRendered() << std::endl;

	app->GetRenderWindow().draw(fpsMeter);
	app->GetRenderWindow().draw(drawnEntities);
}

void GameState::initAssets()
{
	playerTexture1 = app->GetAssetHolder().textures.Get("John1");
	playerTexture2 = app->GetAssetHolder().textures.Get("John2");
	short_beam = app->GetAssetHolder().textures.Get("beam");
	long_beam = app->GetAssetHolder().textures.Get("beam2");

	/*for (int i = 0; i < 5; ++i) {
		buildings[i] = app->GetAssetHolder().textures.Get("building" + i);
	}*/
	buildings[0] = app->GetAssetHolder().textures.Get("building1");
	buildings[1] = app->GetAssetHolder().textures.Get("building2");
	buildings[2] = app->GetAssetHolder().textures.Get("building3");
	buildings[3] = app->GetAssetHolder().textures.Get("building4");
	buildings[4] = app->GetAssetHolder().textures.Get("building5");

	empty = app->GetAssetHolder().textures.Get("null");
}

void GameState::initPlayer()
{
	player = entityCoordinator.CreateEntity();

	vtx::components::Transfrom transform;
	transform.position = vtx::Vec2f(1.0f, -16.0f);
	transform.scale.x = renderSystem->PixelsToMeters(playerTexture1.getSize().x);
	transform.scale.y = renderSystem->PixelsToMeters(playerTexture1.getSize().y);

	vtx::components::Physics physics;
	physics.friction = 0.0f;
	physics.density = 1.0f;

	vtx::components::Renderer renderer;
	renderer.AddAnimation("static", { &playerTexture1 });
	renderer.AddAnimation("walking", { &playerTexture1, &playerTexture2 });
	renderer.SetAnimation("static");

	entityCoordinator.AddComponent(player, transform);
	entityCoordinator.AddComponent(player, renderer);
	entityCoordinator.AddComponent(player, physics);
}

// x is in meters
Block GameState::createBlock(float x)
{ 
	return Block(&entityCoordinator, x, app->GetWidth(), blockCombos[int(floor(vtx::GenRandomFloat(0, blockCombos.size())))], &empty);
}

void GameState::initObstacles()
{
	SetBlockCombos();

	blocks.push_back(createBlock(0.0f));
	blocks.push_back(createBlock(renderSystem->PixelsToMeters(app->GetWidth())));
}

void GameState::controlPlayer()
{
	auto& physics = entityCoordinator.GetComponent<vtx::components::Physics>(player);
	auto& body = entityCoordinator.GetComponent<vtx::components::Physics>(player).body;
	auto& renderer = entityCoordinator.GetComponent<vtx::components::Renderer>(player);

	float moveX = 0.0f;
	float speed = 20.0f + (blockNum);

	if (vtx::InputManager::KeyIsPressed(vtx_key::D)) {
		body->SetLinearVelocity({ speed, body->GetLinearVelocity().y });
		renderer.SetAnimation("walking", 10.0f);
	}
	else if (vtx::InputManager::KeyIsPressed(vtx_key::A)) {
		body->SetLinearVelocity({ -speed, body->GetLinearVelocity().y });
		renderer.SetAnimation("walking", 10.0f, true);
	}
	else renderer.SetAnimation("static", 0.0f, renderer.flipX);

	if (vtx::InputManager::KeyIsPressed(vtx_key::Space) && physics.bottomTouching)
		body->ApplyLinearImpulseToCenter({ 0, body->GetMass() * -10.0f }, true);


	renderSystem->SetXOffset(renderSystem->MetersToPixels(body->GetPosition().x) - (app->GetWidth() / 2) + (playerTexture1.getSize().x / 2) + 300);
	renderSystem->SetYOffset(renderSystem->MetersToPixels(body->GetPosition().y) - (app->GetHeight() / 2) + (playerTexture1.getSize().y / 2) + 300);
}

void GameState::die()
{
	vtx::States::SetCurrentState("DeathState");
}

bool GameState::controlObstacles()
{
	if (renderSystem->GetYOffset() >= 910) {
		die();
		return false;
	}

	if (renderSystem->GetXOffset() >= (blockNum + 1) * app->GetWidth()) {
		++blockNum;
 		blocks[0].ClearEntities();
		blocks.erase(blocks.begin());
		blocks.push_back(createBlock(renderSystem->PixelsToMeters((blockNum + 1) * app->GetWidth())));
	}
	return true;
}
//
//vtx::Entity GameState::createBeam(float x, float y, float friction)
//{
//	vtx::Entity box = entityCoordinator.CreateEntity();
//
//	vtx::components::Transfrom transform;
//	transform.position = vtx::Vec2f(x, y);
//	transform.scale.x = renderSystem->PixelsToMeters(beam.getSize().x);
//	transform.scale.y = renderSystem->PixelsToMeters(beam.getSize().y);
//
//	vtx::components::Physics physics;
//	physics.friction = friction;
//	physics.type = b2_staticBody;
//
//	vtx::components::Renderer renderer;
//	renderer.AddAnimation("static", { &beam });
//	renderer.SetAnimation("static");
//
//	entityCoordinator.AddComponent(box, transform);
//	entityCoordinator.AddComponent(box, renderer);
//	entityCoordinator.AddComponent(box, physics);
//
//	return box;
//}
