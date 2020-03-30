#include "EntityManager.h"

#include <iostream>

namespace vtx
{

	EntityManager::EntityManager()
		: livingEntityCount(0)
	{
		// Create queue of all entity IDs
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			availableEntities.push(entity);
		}
	}

	Entity EntityManager::CreateEntity()
	{
		if (livingEntityCount > MAX_ENTITIES) {
			std::cout << "Entity Overflow Occured. See vtx::EntityManager::CreateEntity() (EntityManager.cpp)" << std::endl;
			return -1;
		}

		Entity id = availableEntities.front();
		availableEntities.pop();
		++livingEntityCount;

		return id;
	}

	void EntityManager::DestroyEntity(Entity entity)
	{
		checkRange(entity, MAX_ENTITIES, "vtx::EntityManager::DestroyEntity(Entity entity)");

		// reset signature at the position in the array
		signatures[entity].reset();

		availableEntities.push(entity);
		--livingEntityCount;
	}

	void EntityManager::SetSignature(Entity entity, Signature signature)
	{
		checkRange(entity, MAX_ENTITIES, "vtx::EntityManager::SetSignature(Entity entity, Signature signature)");

		signatures[entity] = signature;
	}

	Signature EntityManager::GetSignature(Entity entity)
	{
		checkRange(entity, MAX_ENTITIES, "vtx::EntityManager::GetSignature(Entity entity)");

		return signatures[entity];
	}

	void checkRange(Entity entity, uint32_t size, const std::string& funct)
	{
		if (entity > size) {
			std::cout << "Entity id [" << entity << "] out of range. See " + funct + " (EntityManager.cpp)" << std::endl;
			throw;
		}
	}

}
































	//void EntityManager::AddEntity(const Entity& entity)
	//{
	//	AddEntity(entity, GenerateId());
	//}

	//void EntityManager::AddEntity(const Entity& entity, const std::string& id)
	//{
	//	if (entities.count(id) > 0) {
	//		std::cout << "Entity with id [" + id + "] already exists, cannot add it. See (void vtx::EntityManager::AddEntity(const vtx::Entity& entity, const std::string& id) (EntityManager.cpp)" << std::endl;
	//		throw;
	//	}

	//	Entity* e = entity.MakeCopy();
	//	entities[id] = std::unique_ptr<Entity>(e);
	//}

	//void EntityManager::RemoveEntity(const std::string& id)
	//{
	//	entities.erase(id);
	//} 

	//Entity& EntityManager::GetEntity(const std::string& id)
	//{
	//	if (entities.count(id) < 1) {
	//		std::cout << "Entity with id [" + id + "] Not Found. See (vtx::Entity& vtx::EntityManager::GetEntity(const std::string& id) (EntityManager.cpp)" << std::endl;
	//		throw;
	//	}

	//	return (*entities[id]);
	//}

	//void EntityManager::FixedUpdate()
	//{
	//	for (auto iter = entities.begin();
	//		iter != entities.end(); ++iter) {
	//		iter->second->FixedUpdate();
	//	}
	//}

	//void EntityManager::VariableUpdate(float delta)
	//{
	//	for (auto iter = entities.begin(); 
	//		iter != entities.end(); ++iter) {
	//		iter->second->VariableUpdate(delta);
	//	}
	//}

	//void EntityManager::Draw()
	//{
	//	for (auto iter = entities.begin(); 
	//		iter != entities.end(); ++iter) {
	//		iter->second->Draw();
	//	}
	//}

	//std::string EntityManager::GenerateId() const
	//{
	//	return "";
	//}
