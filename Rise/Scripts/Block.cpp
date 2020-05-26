#include "Block.h"

vtx::Entity CreateFloor(vtx::EntityCoordinator* ec, int width, float blockX, float y, sf::Texture* texture)
{
	vtx::Entity obstacle = ec->CreateEntity();

	vtx::components::Transfrom transform;
	transform.position = vtx::Vec2f(blockX, y);

	transform.scale.x = ec->GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(width);
	transform.scale.y = ec->GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(800);

	vtx::components::Physics physics;
	physics.friction = 0.3;
	physics.type = b2_staticBody;

	vtx::components::Renderer renderer;
	renderer.AddAnimation("static", { texture });
	renderer.SetAnimation("static");

	ec->AddComponent(obstacle, transform);
	ec->AddComponent(obstacle, renderer);
	ec->AddComponent(obstacle, physics);

	return obstacle;
}

vtx::Entity CreateObstacle(vtx::EntityCoordinator* ec, const ObstacleInfo& info, float blockX)
{
	vtx::Entity obstacle = ec->CreateEntity();

	vtx::components::Transfrom transform;
	transform.position.x = blockX + info.relativeX;
	transform.position.y = info.absoluteY;

	transform.scale.x = ec->GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(info.texture->getSize().x);
	transform.scale.y = ec->GetSystem<vtx::systems::RenderSystem>()->PixelsToMeters(info.texture->getSize().y);

	vtx::components::Physics physics;
	physics.friction = info.friction;
	physics.type = info.type;

	vtx::components::Renderer renderer;
	renderer.AddAnimation("static", { info.texture });
	renderer.SetAnimation("static");

	ec->AddComponent(obstacle, transform);
	ec->AddComponent(obstacle, renderer);
	ec->AddComponent(obstacle, physics);
	
	return obstacle;
}

Block::Block(vtx::EntityCoordinator* ec, float x, int width, const std::vector<ObstacleInfo>& info, sf::Texture* floorTexture)
	: ec(ec)
	, x(x)
	, width(width)
{
	floor = CreateFloor(ec, width, x, 20, floorTexture);
	for (int i = 0; i < info.size(); ++i) {
		vtx::Entity obstacle = CreateObstacle(ec, info[i], x);
		obstacles.push_back(obstacle);
	}
}

void Block::ClearEntities()
{
	for (int i = 0; i < obstacles.size(); ++i) {
		ec->DestroyEntity(obstacles[i]);
	}
	ec->DestroyEntity(floor);
}
