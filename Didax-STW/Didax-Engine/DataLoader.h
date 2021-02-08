#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <SFML/System.hpp>
#include <Windows.h>
#include <stringapiset.h>

#include <nlohmann/json.hpp>


#include "Logger.h"

namespace Didax 
{
	class DataLoader
	{
	public:

		//static void createTexturesDat(const std::vector<std::string>& filenames);
		//static void createAudioDat(const std::vector<std::string>& filenames);
		//static void createAssetsDat(const std::vector<std::string>& filenames);

		static nlohmann::json loadJsonFromFile(const std::string& filename);
		static sf::String sfStringFromJson(const nlohmann::json& json);
	};

}


