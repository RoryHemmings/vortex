#include "Coordinator.h"

namespace vtx
{

	void Coordinator::Init()
	{
		entityManager = std::make_unique<EntityManager>();
		componentManager = std::make_unique<ComponentManager>();
		systemManager = std::make_unique<SystemManager>();
	}

	Entity Coordinator::CreateEntity() const
	{
		return entityManager->CreateEntity();
	}

	void Coordinator::DestroyEntity(Entity entity)
	{
		entityManager->DestroyEntity(entity);
		componentManager->EntityDestroyed(entity);
		systemManager->EntityDestroyed(entity);
	}

}
