#pragma once

#ifndef VTX_COMPONENT_MANAGER_H
#define VTX_COMPONENT_MANAGER_H

#include <array>
#include <unordered_map>
#include <string>
#include <memory>

#include <iostream>

#include "../entities/EntityManager.h"

namespace vtx
{
	class IComponentArray
	{

	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;

	};

	template <class T>
	class ComponentArray : public IComponentArray
	{

	public:
		/*
			Definitions are in header file to prevent linker errors
			With template class
		*/

		void InsertData(Entity entity, T component)
		{
			if (entityToIndexMap.count(entity) > 0) {
				std::cout << "Entity + [" << entity << "] already has component. See void vtx::ComponentManager<T>::InsertData(Entity entity, T component) (ComponentManager.h)" << std::endl;
				return;
			}

			/*
				Add component to end of array
				Adjust maps so that the entity
				ID points to its index and the
				index points to the entity
			*/
			size_t end = size;
			entityToIndexMap[entity] = end;
			indexToEntityMap[end] = entity;
			componentArray[entity] = component;
			++size;
		}

		void RemoveData(Entity entity)
		{
			if (entityToIndexMap.count(entity) < 1) {
				std::cout << "Attempting to remove non-existent component from Entity + [" << entity << "]. See void vtx::ComponentManager<T>::RemoveData(Entity entity) (ComponentManager.h)" << std::endl;
				return;
			}

			size_t indexOfRemovedEntity = entityToIndexMap[entity];
			size_t indexOfLastElement = size - 1;
			componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

			Entity lastEntity = indexToEntityMap[indexOfLastElement];
			entityToIndexMap[lastEntity] = indexOfRemovedEntity;
			indexToEntityMap[indexOfRemovedEntity] = lastEntity;

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(indexOfLastElement);

			--size;
		}

		T& GetData(Entity entity)
		{
			if (entityToIndexMap.count(entity) < 1) {
				std::cout << "No Component on Entity [" << entity << "] exists. See T& vtx::ComponentManager<T>::GetData(Entity entity) (ComponentManager.h)" << std::endl;
				throw;
			}

			return componentArray[entityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity)
		{
			// If entity has this component, then remove it
			if (entityToIndexMap.count(entity) > 0) {
				RemoveData(entity);
			}
		}

	private:
		std::array<T, MAX_ENTITIES> componentArray;
		std::unordered_map<Entity, size_t> entityToIndexMap;
		std::unordered_map<size_t, Entity> indexToEntityMap;

		size_t size;

	};

	class ComponentManager
	{

	public:
		template <class T>
		void RegisterComponent()
		{
			std::string typeName = typeid(T).name();

			if (componentTypes.count(typeName) > 0) {
				//std::cout << "Component [" + typeName + "] already exists. See void ComponentManager::RegisterComponent() (ComponentManager.h)" << std::endl;
				return;
			}

			componentTypes.insert({typeName, nextComponentType});
			componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

			++nextComponentType;
		}

		template <class T>
		ComponentType GetComponentType()
		{
			std::string typeName = typeid(T).name();

			if (componentTypes.count(typeName) < 1) {
				std::cout << "Component + [" << typeName << "] is not registered. See ComponentType ComponentManager::GetComponentType() (ComponentManager.h)" << std::endl;
				throw;
			}

			return componentTypes[typeName];
		}

		template <class T>
		void AddComponent(Entity entity, T component)
		{
			/* 
				Get component array of type component 
				Add component to array and link to entity ID
			*/
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template <class T>
		void RemoveComponent(Entity entity)
		{
			// Parameter of component type is implied through template
			GetComponentArray<T>()->RemoveData(entity);
		}

		template <class T>
		T& GetComponent(Entity entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(Entity entity)
		{
			/*
				Loop through all component arrays
				tell all of them to remove their
				components from entity entity
			*/
			for (const auto& pair : componentArrays) {
				const auto& componentArray = pair.second;
				componentArray->EntityDestroyed(entity);
			}
		}

	private:
		template <class T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			std::string typeName = typeid(T).name();

			if (componentTypes.count(typeName) < 1) {
				std::cout << "No Component + [" << typeName << "] exists. See std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() (ComponentManager.h)" << std::endl;
				throw;
			}

			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
		}

	private:
		std::unordered_map<std::string, ComponentType> componentTypes;
		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays;

		ComponentType nextComponentType;

	};

}

#endif
