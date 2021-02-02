#pragma once
#include "Asset.h"

#include <SFML/Graphics.hpp>

namespace Didax
{

	class AudioAsset : public Asset
	{
	public:
		AudioAsset(const std::string& name);

		virtual void loadAsset(const nlohmann::json& asset) override;

	public:

	};

}

