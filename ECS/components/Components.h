#pragma once

#ifndef VTX_COMPONENTS_H
#define VTX_COMPONENTS_H

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "../../util/Math.h"

namespace vtx
{
	typedef uint8_t ComponentType;
	const uint8_t MAX_COMPONENTS = 255;

	namespace components
	{

		struct Transfrom
		{
			// In METERS
			Vec2f position = { 0.0f, 0.0f };
			Vec2f scale = { 1.0f, 1.0f };

			// In radians
			float rotation = 0.0f;
		};

		struct Physics
		{
			/* 
				Memory is managed by box2d,
				no need for smart pointer
			*/
			b2Body* body;
			b2Fixture* bottom;

			b2BodyType type = b2_dynamicBody;

			float density = 0.0f;
			float friction = 0.0f;

			bool topTouching = false;
			bool bottomTouching = false;
			bool leftTouching = false;
			bool rightTouching = false;

			void (*CollisionCallback)(Physics*) = nullptr;
		};

		struct Renderer
		{
			// Animation name to vector of frame pointers
			std::unordered_map<std::string, std::vector<sf::Texture*>> animations;
			sf::VertexArray quad = sf::VertexArray(sf::Quads, 4);

			float millisecondsPerFrame = -1.0f;
			int frameIndex = 0;
			int millisecondsSinceLastFrame = 0;

			std::string currentAnimation;
		
			void AddAnimation(const std::string& name, const std::vector<sf::Texture*>& frames);
			void SetAnimation(const std::string& name, float fps=0.0f, bool flipX = false, bool flipY = false);

			bool flipX = false;
			bool flipY = false;
		};

	}

}

#endif



//@ - 1, 29 + 0, 0 @@
//#pragma once
//
//#ifndef VTX_COMPONENT_H
//#define VTX_COMPONENT_H
//
//#include <string>
//
//namespace vtx
//{
//
//	class Application;
//
//	class Component
//	{
//
//	public:
//		Component()
//		{ }
//		virtual ~Component() { }
//
//		virtual void FixedUpdate(Application* app) = 0;
//		virtual void VariableUpdate(Application* app, float delta) = 0;
//		virtual void Draw(Application* app) = 0;
//
//	};
//
//}
//
//#endif
