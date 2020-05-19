#pragma once

#ifndef VTX_ASSET_HOLDER_H
#define VTX_ASSET_HOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>

#include "AssetManager.h"

namespace vtx
{

	class AssetHolder
	{

	public:
		AssetHolder(const std::string& parentFolder);

		AssetManager<sf::Texture> textures;
		AssetManager<sf::Font> fonts;

	};

}

#endif

