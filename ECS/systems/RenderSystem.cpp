#include "RenderSystem.h"

#include <iostream>

#include <SFML/System.hpp>

#include "../../core/Application.h"
#include "../../util/Math.h"

namespace vtx
{
	namespace systems
	{

		void RenderSystem::Draw(Application* app, EntityCoordinator* entityCoordinator)
		{
			for (const auto& entity : entities) {
				auto& renderer = entityCoordinator->GetComponent<vtx::components::Renderer>(entity);
				const auto& transform = entityCoordinator->GetComponent<vtx::components::Transfrom>(entity);
				const auto& texture = renderer.texture;

				const float x = transform.position.x;
				const float y = transform.position.y;

				const float width = texture.getSize().x * transform.scale.x;
				const float height = texture.getSize().y * transform.scale.y;

				renderer.quad[0].position = sf::Vector2f(x, y);
				renderer.quad[1].position = sf::Vector2f(x + width, y);
				renderer.quad[2].position = sf::Vector2f(x + width, y + height);
				renderer.quad[3].position = sf::Vector2f(x, y + height);

				renderer.quad[0].texCoords = sf::Vector2f(0, 0);
				renderer.quad[1].texCoords = sf::Vector2f(width, 0);
				renderer.quad[2].texCoords = sf::Vector2f(width, height);
				renderer.quad[3].texCoords = sf::Vector2f(0, height);


				app->GetRenderWindow().draw(renderer.quad, &texture);
			}
		}
	}

}
