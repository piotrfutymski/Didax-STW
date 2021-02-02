#include "TextureAsset.h"

Didax::TextureAsset::TextureAsset(const std::string& name):Asset(name)
{
}

void Didax::TextureAsset::loadAssetRaw(const nlohmann::json& asset)
{
	sf::Image i;
	i.loadFromFile(asset["path"]);
	i.createMaskFromColor(sf::Color{ 255,255,255,255 });
	texture.loadFromImage(i);
}

void Didax::TextureAsset::loadAssetBin(const nlohmann::json& asset)
{
}
