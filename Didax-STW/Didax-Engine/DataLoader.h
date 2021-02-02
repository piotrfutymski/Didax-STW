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

		static void createTexturesDat(const std::vector<std::string>& filenames);
		static void createAudioDat(const std::vector<std::string>& filenames);
		static void createAssetsDat(const std::vector<std::string>& filenames);

		static nlohmann::json loadJsonFromFile(const std::string& filename);
	};

}


