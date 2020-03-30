#pragma once

#ifndef VTX_ENTITY_MANAGER_H
#define VTX_ENTITY_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <array>

#include "../components/Components.h"

namespace vtx
{

	/* Entitys are essentially just IDs that reference
		a group of components (a Signature)
	*/
	typedef uint32_t Entity;
	const uint32_t MAX_ENTITIES = 5000;

	/* Keeps track of which components an entity has
		Ex: it has transform, physics but no renderer
		{ 1, 1, 0 }
	*/
	typedef std::bitset<vtx::MAX_COMPONENTS> Signature;

	class EntityManager
	{

	public:
		EntityManager();

		/* Entity is just an integer therefore
		   no reference or const declaration
		   is required in parameter definitions
		*/
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void SetSignature(Entity entity, Signature signature);
		Signature GetSignature(Entity entity);


	private:
		// Unused Entity IDs
		std::queue<Entity> availableEntities;

		// Array of signatures. Index Corresponds to Entity ID
		std::array<Signature, MAX_ENTITIES> signatures;

		// Total living entities.
		uint32_t livingEntityCount;

	};

}














	//class Application;

	//class EntityManager
	//{
	//	
	//public:
	//	EntityManager(Application* app)
	//		: app(app)
	//	{ }

	//	/*
	//		Providing EntityId is optional, 
	//		so it will be uniquely generated
	//		if you dont need to worry about
	//		accessing it again

	//		Initialize Entitys as local variables
	//		so that they can be COPIED and stored 
	//		in this class instead of globally or 
	//		in another class
	//	*/
	//	void AddEntity(const Entity& entity);
	//	void AddEntity(const Entity& entity, const std::string& id);

	//	void RemoveEntity(const std::string& id);

	//	Entity& GetEntity(const std::string& id);

	//	void FixedUpdate();
	//	void VariableUpdate(float delta);
	//	void Draw();

	//private:
	//	std::string GenerateId() const;

	//private:
	//	std::unordered_map<std::string, std::unique_ptr<Entity>> entities;

	//	Application* app;

	//};

#endif

// Will be implemented as an interface and then methods will be called from inside
