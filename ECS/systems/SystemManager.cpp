#include "SystemManager.h"

namespace vtx
{
	void SystemManager::EntityDestroyed(Entity entity)
	{
		for (const auto& pair : systems) {
			const auto& system = pair.second;

			system->entities.erase(entity);
		}
	}

	void SystemManager::EntitySignatureChange(Entity entity, const Signature& entitySignature)
	{
		for (const auto& pair : systems)
		{
			const auto& type = pair.first;
			const auto& system = pair.second;
			const auto& systemSignature = signatures[type];

			// If entity has the components asked for in signature
			// Not exclusively the same, but if it contains them 
			if ((entitySignature & systemSignature) == systemSignature) {
				// Entity has added component that makes it elibible for this system
				system->entities.insert(entity);
			}
			else {
				// Entity has removed component that makes it invalid for this system
				system->entities.erase(entity);
			}
		}
	}
}
