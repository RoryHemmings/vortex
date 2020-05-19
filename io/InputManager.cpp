#include "InputManager.h"

namespace vtx
{
	bool InputManager::KeyIsPressed(vtx_key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
}
