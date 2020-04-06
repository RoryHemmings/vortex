#include "PhysicsSystem.h"

#include "../../core/Application.h"
#include "../EntityCoordinator.h"

namespace vtx
{
	namespace systems
	{
		void PhysicsSystem::FixedUpdate(Application* app, EntityCoordinator* entityCoordinator)
		{
			for (const auto& entity : entities) {
				auto& physics = entityCoordinator->GetComponent<vtx::components::Physics>(entity);
				auto& transform = entityCoordinator->GetComponent <vtx::components::Transfrom>(entity);

				// Increase y velocity by gravity
				// If moving down, accelerate faster, makes object feel heavier
				if (physics.gravity > 0)
					physics.velocity.y += physics.gravity * 1.4;
				else
					physics.velocity.y += physics.gravity;

				if (transform.position.y > app->GetHeight() - 100) {
					physics.velocity.y = -750;
				}

				// Update Position based on velocity
				transform.position.x += physics.velocity.x * app->GetFixedDelta();
				transform.position.y += physics.velocity.y * app->GetFixedDelta();
			}
		}
	}
}
