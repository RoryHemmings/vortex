#pragma once

#ifndef VTX_ENTITY_H
#define VTX_ENTITY_H

#include <vector>
#include <string>

#include "../components/Component.h"

namespace vtx
{

	class Application;

	class Entity
	{

	public:
		Entity(Application* app)
			: app(app)
			{ }

		/*Entity(double x, double y)
			needs transform as default component
		{ }*/

		virtual void FixedUpdate() = 0;
		virtual void VariableUpdate(float delta) = 0;
		virtual void Draw() = 0;

		virtual ~Entity() { }

	protected:
		// unsigned int id;
		Application* app;

	};

}

#endif
