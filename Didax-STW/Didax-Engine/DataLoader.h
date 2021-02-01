#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <exception>

#include <nlohmann/json.hpp>

namespace Didax 
{
	class DataLoader
	{
	public:
		static void saveJsonToBin(const nlohmann::json& json, const std::string& outFile);

		static nlohmann::json jsonFromBinFile(const std::string& inFile);

		static void createTexturesDat(const std::vector<std::string>& filenames);
		static void createAudioDat(const std::vector<std::string>& filenames);
		static void createAssetsDat(const std::vector<std::string>& filenames);
	};

}


