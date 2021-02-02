#pragma once
#include "Asset.h"

#include <SFML/Graphics.hpp>

namespace Didax
{

	class TextureAsset : public Asset
	{
	public:
		TextureAsset(const std::string& name);

		virtual void loadAsset(const nlohmann::json& asset) override;

	public:

		sf::Texture texture;
		
	};

}
