#pragma once

#ifndef VTX_COMPONENTS_H
#define VTX_COMPONENTS_H

#include <string>

#include <SFML/Graphics.hpp>

#include "../../util/Math.h"

namespace vtx
{
	typedef uint8_t ComponentType;
	const uint8_t MAX_COMPONENTS = 64;

	namespace components
	{

		struct Transfrom
		{
			Vec2f position = { 0.0f, 0.0f };
			float rotation = 0.0;
			Vec2f scale = { 1.0f, 1.0f };
		};

		struct Physics
		{
			// Pixels per second
			Vec2f velocity = { 0.0f, 0.0f };
			float gravity = 35.0f;
		};

		struct Collider
		{
			
		};

		struct Renderer
		{
			sf::Texture texture;
			sf::VertexArray quad = sf::VertexArray(sf::Quads, 4);
		};

		//class TransformComponent : public Component
		//{

		//public:
		//	TransformComponent(double x, double y, double scaleX=1.0, double scaleY=1.0, double xRot=0.0, double yRot=0.0)
		//		: x(x)
		//		, y(y)
		//		, scaleX(scaleX)
		//		, scaleY(scaleY)
		//		, xRot(xRot)
		//		, yRot(yRot)
		//	{}

		//	void FixedUpdate(Application* app) { }
		//	void VariableUpdate(Application* app, float delta) { }
		//	void Draw(Application* app) { }

		//	// need scale as well

		//	double GetX() const { return x; }
		//	double GetY() const { return y; }
		//	double GetScaleX() const { return scaleX; }
		//	double GetScaleY() const { return scaleY; }
		//	double GetXRotation() const { return xRot; }
		//	double GetYRotation() const { return yRot; }

		//	void SetX(double x) { this->x = x; }
		//	void SetY(double y) { this->y = y; }
		//	void SetScaleX(double scaleX) { this->scaleX; }
		//	void SetScaleY(double scaleY) { this->scaleY; }
		//	void SetXRotation(double xRot) { this->xRot = xRot; }
		//	void SetYRotation(double yRot) { this->yRot = yRot; }

		//protected:
		//	double x, y, xRot, yRot, scaleX, scaleY;

		//};

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
