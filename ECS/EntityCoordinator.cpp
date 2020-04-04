#include "EntityCoordinator.h"

namespace vtx
{

	void EntityCoordinator::Init()
	{
		entityManager = std::make_unique<EntityManager>();
		componentManager = std::make_unique<ComponentManager>();
		systemManager = std::make_unique<SystemManager>();
	}

	void EntityCoordinator::Clear()
	{
		// Destroy Manager Objects, Make the EntityCoordinator hollow
		entityManager.reset();
		componentManager.reset();
		systemManager.reset();
	}

	Entity EntityCoordinator::CreateEntity() const
	{
		return entityManager->CreateEntity();
	}

	void EntityCoordinator::DestroyEntity(Entity entity)
	{
		entityManager->DestroyEntity(entity);
		componentManager->EntityDestroyed(entity);
		systemManager->EntityDestroyed(entity);
	}

}
