#pragma once

#ifndef VTX_COMPONENT_H
#define VTX_COMPONENT_H

#include <string>

namespace vtx
{

	class Application;

	class Component
	{

	public:
		Component()
		{ }
		virtual ~Component() { }
		
		virtual void FixedUpdate(Application* app) = 0;
		virtual void VariableUpdate(Application* app, float delta) = 0;
		virtual void Draw(Application* app) = 0;

	};

}

#endif
