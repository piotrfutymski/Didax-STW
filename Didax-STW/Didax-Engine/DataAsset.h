#pragma once
#include "Asset.h"

#include <SFML/Graphics.hpp>

namespace Didax
{

	class DataAsset : public Asset
	{
	public:
		DataAsset(const std::string& name);

		virtual void loadAsset(const nlohmann::json& asset) override;

	public:

	};

}