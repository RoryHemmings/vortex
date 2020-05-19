#pragma once

#ifndef VTX_INPUT_MANAGER_H
#define VTX_INPUT_MANAGER_H

#include <SFML/Window.hpp>

namespace vtx
{

	#define vtx_key sf::Keyboard::Key

	class InputManager
	{

	public:
		static bool KeyIsPressed(vtx_key key);

	private:


	};

}

#endif
