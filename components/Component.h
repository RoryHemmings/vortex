#pragma once

#ifndef VTX_COMPONENT_H
#define VTX_COMPONENT

#include <string>

namespace vtx
{

	class Component
	{

	public:
		Component(const std::string& name)
			: name(name)
		{ }
		
		virtual void draw() = 0;

		virtual const std::string GetName() const { return name; }

		virtual ~Component() { }

	private:
		std::string name;

	};

}

#endif
