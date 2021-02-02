#include "AssetManager.h"

Didax::AssetManager::AssetManager()
{
}

bool Didax::AssetManager::loadAssets(const std::string& filename, bool assetPacked)
{
	if (assetPacked)
		return loadAssetsFromBinary(filename);
	return loadAssetsFromRaw(filename);
}

bool Didax::AssetManager::saveAssets(const std::string& assetfilename, bool assetPacked)const
{
	return true;
}

bool Didax::AssetManager::loadAssetsFromBinary(const std::string& assetfilename)
{
	return false;
}

bool Didax::AssetManager::loadAssetsFromRaw(const std::string& assetfilename)
{
	try {
		auto asetsCategory = std::move(DataLoader::loadJsonFromFile(assetfilename));
		for (auto& filename : asetsCategory)
			loadAssetsFromFile(filename["path"]);
	}
	catch (const std::exception&) {
#ifdef _DEBUG
		std::cout << "Unable to load file " << assetfilename << std::endl;
#endif // _DEBUG
		return false;
	}
	return true;
}

void Didax::AssetManager::loadAssetsFromFile(const std::string& filename)
{
	try {
		auto assetJson = std::move(DataLoader::loadJsonFromFile(filename));
		for (nlohmann::json::iterator it = assetJson.begin(); it != assetJson.end(); ++it)
		{
			Asset* a;
			if (it.value()["type"] == "audio")
				a = createAsset<AudioAsset>(it.key());
			else if (it.value()["type"] == "data")
				a = createAsset<DataAsset>(it.key());
			else if (it.value()["type"] == "font")
				a = createAsset<FontAsset>(it.key());
			else if (it.value()["type"] == "texture")
				a = createAsset<DataAsset>(it.key());
			else
				continue;
			a->loadAsset(it.value());
		}
	}
	catch (const std::exception& ) {
#ifdef _DEBUG
		std::cout << "Unable to load assets from file: " << filename << std::endl;
#endif // _DEBUG
	}
}


