#include "Entity.h"

namespace vtx
{

	Component& Entity::GetComponent(const std::string& name)
	{
		std::vector<Component>::iterator iter = components.begin();
		while (iter != components.end()) {
			if (name == iter->GetName()) {
				return *iter;
			}
			++iter;
		}

		throw "Entity has no component " + name;
	}

}
