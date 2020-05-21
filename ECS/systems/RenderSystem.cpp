#include "RenderSystem.h"

#include <iostream>

#include <SFML/System.hpp>

#include "../../core/Application.h"
#include "../../util/Math.h"

namespace vtx
{
	namespace systems
	{

		void RenderSystem::OnMemberAddition(Entity entity)
		{
			numEntitiesRendered++;

			auto& transform = entityCoordinator->GetComponent<vtx::components::Transfrom>(entity);
			auto& renderer = entityCoordinator->GetComponent<vtx::components::Renderer>(entity);
		}

		void RenderSystem::OnMemberDestruction(Entity entity)
		{
			numEntitiesRendered--;
		}

		void RenderSystem::FixedUpdate()
		{
			for (const auto& entity : entities) {
				auto& renderer = entityCoordinator->GetComponent<vtx::components::Renderer>(entity);
				const auto& animation = renderer.animations[renderer.currentAnimation];
				if (animation.size() > 1) {
					if (renderer.millisecondsSinceLastFrame > renderer.millisecondsPerFrame && renderer.millisecondsPerFrame != -1) {
						renderer.frameIndex = (renderer.frameIndex == (animation.size() - 1)) ? 0 : renderer.frameIndex + 1;
						renderer.millisecondsSinceLastFrame = 0;
					}
					else {
						renderer.millisecondsSinceLastFrame += app->GetFixedDelta() * 1000;
					}
				}
			}
		}

		// TODO: Only draw entities that appear on screen
		void RenderSystem::Draw()
		{
			for (const auto& entity : entities) {
				auto& renderer = entityCoordinator->GetComponent<vtx::components::Renderer>(entity);
				const auto& animation = renderer.animations[renderer.currentAnimation];
				const auto& transform = entityCoordinator->GetComponent<vtx::components::Transfrom>(entity);

				const auto& texture = *(animation[renderer.frameIndex]);	// Dereference pointer to frame

				const float x = (transform.position.x * pixelToMeterRatio) - xOffset;
				const float y = (transform.position.y * pixelToMeterRatio) - yOffset;

				const float width = transform.scale.x * pixelToMeterRatio;
				const float height = transform.scale.y * pixelToMeterRatio;

				renderer.quad[0].position = sf::Vector2f(x, y);
				renderer.quad[1].position = sf::Vector2f(x + width, y);
				renderer.quad[2].position = sf::Vector2f(x + width, y + height);
				renderer.quad[3].position = sf::Vector2f(x, y + height);

				if (!renderer.flipX) {
					renderer.quad[0].texCoords = sf::Vector2f(0, 0);
					renderer.quad[1].texCoords = sf::Vector2f(width, 0);
					renderer.quad[2].texCoords = sf::Vector2f(width, height);
					renderer.quad[3].texCoords = sf::Vector2f(0, height);
				}
				else
				{
					renderer.quad[1].texCoords = sf::Vector2f(0, 0);
					renderer.quad[0].texCoords = sf::Vector2f(width, 0);
					renderer.quad[3].texCoords = sf::Vector2f(width, height);
					renderer.quad[2].texCoords = sf::Vector2f(0, height);
				}

				app->GetRenderWindow().draw(renderer.quad, &texture);
			}
		}
	}

}
