#include "AssetHolder.h"

namespace vtx
{

	AssetHolder::AssetHolder(const std::string& parentFolder)
		: textures(parentFolder, "textures", "png")
		, fonts(parentFolder, "fonts", "ttf")
		{ }

}
