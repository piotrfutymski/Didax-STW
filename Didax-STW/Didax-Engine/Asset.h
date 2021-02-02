#pragma once

#include "DataLoader.h"

namespace Didax
{

	class Asset
	{
	public:

		Asset(const std::string& name);

		virtual void loadAssetRaw(const nlohmann::json& asset) = 0;

		virtual void loadAssetBin(const nlohmann::json& asset) = 0;

		const std::string& getName()const;

	protected:

		std::string m_name;

	};

}

