#pragma once

#ifndef VTX_COORDINATOR_H
#define VTX_COORDINATOR_H

#include <memory>

#include "entities/EntityManager.h"
#include "components/ComponentManager.h"
#include "systems/SystemManager.h"

namespace vtx
{
	
	class EntityCoordinator
	{

	public:
		void Init();

		// Makes all managers hollow (Null pointers)
		void Clear();

		Entity CreateEntity() const;
		void DestroyEntity(Entity entity);
		
		template <class T>
		void RegisterComponent()
		{
			componentManager->RegisterComponent<T>();
		}

		template <class T>
		void AddComponent(Entity entity, T component)
		{
			componentManager->AddComponent<T>(entity, component);

			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), true);
			entityManager->SetSignature(entity, signature);

			systemManager->EntitySignatureChange(entity, signature);
		}

		template <class T>
		void RemoveComponent(Entity entity)
		{
			componentManager->RemoveComponent<T>(entity);

			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), false);
			entityManager->SetSignature(entity, signature);

			systemManager->EntitySignatureChange(entity, signature);
		}

		template <class T>
		T& GetComponent(Entity entity)
		{
			return componentManager->GetComponent<T>(entity);
		}

		template <class T>
		ComponentType GetComponentType()
		{
			return componentManager->GetComponentType<T>();
		}

		template <class T>
		std::shared_ptr<T> RegisterSystem()
		{
			return systemManager->RegisterSystem<T>();
		}

		template <class T>
		std::shared_ptr<T> GetSystem()
		{
			return systemManager->GetSystem<T>();
		}

		template <class T>
		void SetSystemSignature(const Signature& signature)
		{
			systemManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<SystemManager> systemManager;

	};

}

#endif
