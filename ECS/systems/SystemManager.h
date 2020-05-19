#pragma once

#ifndef VTX_SYSTEM_H
#define VTX_SYSTEM_H

#include <set>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <cstdarg>

#include "../entities/EntityManager.h"

namespace vtx
{
	class Application;
	class EntityCoordinator;

	class System
	{

	public:
		System(Application* a, EntityCoordinator* ec) { app = a; entityCoordinator = ec; }

		// Initializes new Entity upon addition to system
		virtual void OnMemberAddition(Entity member) { };
		virtual void OnMemberDestruction(Entity member) { };

		virtual void FixedUpdate() { }
		virtual void VariableUpdate(float delta) { }
		virtual void Draw() { }

		std::set<Entity> entities;

	protected:
		Application* app;
		EntityCoordinator* entityCoordinator;

	};

	class SystemManager
	{

	public:
		template <class T, class... Args>
		std::shared_ptr<T> RegisterSystem(Application* app, EntityCoordinator* ec, Args... args)
		{
			std::string typeName = typeid(T).name();

			if (systems.count(typeName) > 0) {
				// Attempting to register system twice
				return std::static_pointer_cast<T>(systems[typeName]);
			}

			auto system = std::make_shared<T>(app, ec, args...);

			systems.insert({ typeName, system });

			return system;
		}

		template <class T>
		std::shared_ptr<T> GetSystem()
		{
			std::string typeName = typeid(T).name();

			if (systems.count(typeName) < 1) {
				std::cout << "System [" + typeName + "] has not been registered. See std::shared_ptr<T> SystemManager::GetSystem() (SystemManager.h)" << std::endl;
				throw;
			}

			return std::static_pointer_cast<T>(systems[typeName]);
		}

		template <class T>
		void SetSignature(const Signature& signature)
		{
			std::string typeName = typeid(T).name();

			if (systems.count(typeName) < 1) {
				std::cout << "Attempting to set signature of system [" + typeName + "] before it has been registered. see void SystemManager::SetSignature(const Signature& signature) (SystemManager.h)" << std::endl;
				throw;
			}

			signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(Entity entity);
		void EntitySignatureChange(Entity entity, const Signature& entitySignature);

	private:
		std::unordered_map<std::string, Signature> signatures;
		std::unordered_map<std::string, std::shared_ptr<System>> systems;

	};

}

#include "Systems.h"

#endif
