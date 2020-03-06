#pragma once

#ifndef VTX_ENTITY_H
#define VTX_ENTITY_H

#include <vector>
#include <string>

#include "../components/Component.h"

namespace vtx
{

	class Entity
	{

	public:
		Entity() { }

		/*Entity(double x, double y)
			needs transform as default component
		{ }*/

		Component& GetComponent(const std::string&);

		virtual ~Entity() { }

	private:
		// unsigned int id;
		std::vector<Component> components;

	};

}

#endif
