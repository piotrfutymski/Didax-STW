#include "FontAsset.h"

Didax::FontAsset::FontAsset(const std::string& name):Asset(name)
{
}

void Didax::FontAsset::loadAsset(const nlohmann::json& asset)
{
	font.loadFromFile(asset["path"]);
}
