#pragma once
#include "Asset.h"

#include <SFML/Graphics.hpp>

namespace Didax
{

	class FontAsset : public Asset
	{
	public:
		FontAsset(const std::string& name);

		virtual void loadAsset(const nlohmann::json& asset) override;

	public:

		sf::Font font;

	};

}
