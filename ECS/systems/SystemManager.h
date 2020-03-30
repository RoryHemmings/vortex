#pragma once

#ifndef VTX_SYSTEM_H
#define VTX_SYSTEM_H

#include <set>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include "../entities/EntityManager.h"

namespace vtx
{

	class System
	{

	public:
		std::set<Entity> entities;

	};

	class SystemManager
	{

	public:
		template <class T>
		std::shared_ptr<T> RegisterSystem()
		{
			std::string typeName = typeid(T).name();

			if (systems.count(typeName) > 0) {
				// Attempting to register system twice
				return;
			}

			auto system = std::make_shared<T>();
			systems.insert({ typeName, system });
			return system;
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

#endif
