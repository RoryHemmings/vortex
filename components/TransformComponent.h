#pragma once

#ifndef VTX_TRANSFORM_COMPONENT_H
#define VTX_TRANSFORM_COMPONENT_H

#include <string>

#include "Component.h"

namespace vtx
{

	class TransformComponent : public Component
	{

	public:
		TransformComponent(double x, double y, double scaleX=1.0, double scaleY=1.0, double xRot=0.0, double yRot=0.0)
			: x(x)
			, y(y)
			, scaleX(scaleX)
			, scaleY(scaleY)
			, xRot(xRot)
			, yRot(yRot)
		{}

		void FixedUpdate(Application* app) { }
		void VariableUpdate(Application* app, float delta) { }
		void Draw(Application* app) { }

		// need scale as well

		double GetX() const { return x; }
		double GetY() const { return y; }
		double GetScaleX() const { return scaleX; }
		double GetScaleY() const { return scaleY; }
		double GetXRotation() const { return xRot; }
		double GetYRotation() const { return yRot; }

		void SetX(double x) { this->x = x; }
		void SetY(double y) { this->y = y; }
		void SetScaleX(double scaleX) { this->scaleX; }
		void SetScaleY(double scaleY) { this->scaleY; }
		void SetXRotation(double xRot) { this->xRot = xRot; }
		void SetYRotation(double yRot) { this->yRot = yRot; }

	protected:
		double x, y, xRot, yRot, scaleX, scaleY;

	};

}

#endif
