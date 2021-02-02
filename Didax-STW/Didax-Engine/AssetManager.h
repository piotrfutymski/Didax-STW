#pragma once

#include <memory>
#include <map>

#include "AudioAsset.h"
#include "DataAsset.h"
#include "FontAsset.h"
#include "TextureAsset.h"

namespace Didax
{

	class AssetManager
	{
	public:

		using AssetHolder_t = std::map<std::string, std::unique_ptr<Asset>>;

		AssetManager();

		bool loadAssets(const std::string& assetfilename, bool assetPacked);

		bool saveAssets(const std::string& assetfilename, bool assetPacked)const;


		template<typename T>
		typename std::enable_if<std::is_base_of<Asset, T>::value, T>::type* createAsset(const std::string name)
		{
			m_assets[name] = std::make_unique<T>(name);
			return static_cast<T*> (m_assets[name].get());
		}

		template <typename T>
		typename std::enable_if<std::is_base_of<Asset, T>::value, T>::type* getAsset(const std::string name)
		{
			if (m_assets.find(name) == m_assets.end())
				return nullptr;
			else
				return static_cast<T*> (m_assets[name].get());
		}

	private:

		AssetHolder_t m_assets;

	private:

		bool loadAssetsFromBinary(const std::string& assetfilename);

		bool loadAssetsFromRaw(const std::string& assetfilename);
		void loadAssetsFromFile(const std::string& filename);

	};

}

