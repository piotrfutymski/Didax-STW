#pragma once
#include "Asset.h"

#include <SFML/Graphics.hpp>

namespace Didax
{

	class AudioAsset : public Asset
	{
	public:
		AudioAsset(const std::string& name);

		virtual void loadAssetRaw(const nlohmann::json& asset) override;

		virtual void loadAssetBin(const nlohmann::json& asset) override;

	public:

	};

}

