#pragma once

#ifndef VTX_ASSET_MANAGER_H
#define VTX_ASSET_MANAGER_H

#include <unordered_map>
#include <utility>
#include <string>

namespace vtx
{

	template <class AssetType>
	class AssetManager
	{
		 
	public:
		AssetManager(const std::string parentFolder, const std::string& folder, const std::string& extension) 
			: folder(parentFolder + '/' + folder + '/')
			, extension('.' + extension)
			{ }

		/*
			The user only has to define the file folder
			and the extension, nothing else. When they
			attempt to call Get() on an asset, the 
			manager will search the folder to find it.
		*/
		const AssetType& Get(const std::string& name)
		{
			if (!Exists(name)) {
				Add(name);
			}

			return assets.at(name);
		}

		void Add(const std::string& name)
		{
			AssetType asset;

			if (asset.loadFromFile(getFullFilename(name))) {
				assets.insert(std::make_pair(name, asset));
			}
			else {
				AssetType fail;
				fail.loadFromFile(folder + "null" + extension);
				assets.insert(std::make_pair(name, fail));
			}
		}

		bool Exists(const std::string& name) const
		{
			return (assets.find(name) != assets.end());
		}

	private:
		std::string getFullFilename(const std::string& name) const
		{
			return folder + name + extension;
		}

		const std::string folder;
		const std::string extension;

		std::unordered_map<std::string, AssetType> assets;

	};

}

#endif
