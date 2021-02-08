#include "DataLoader.h"

nlohmann::json Didax::DataLoader::loadJsonFromFile(const std::string& filename)
{
	nlohmann::json res;
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		Logger::log("Unable to open json file: " + filename);
	}
	try {
		stream >> res;
	}
	catch (std::exception& e) {
		Logger::log("Unable to read from json file: " + filename);
		Logger::log("Reason: " + std::string(e.what()),Logger::Level::Info);
	}
	return res;
}

sf::String Didax::DataLoader::sfStringFromJson(const nlohmann::json& json)
{
	std::string str = json.get<std::string>();
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring tmp;
	tmp.resize(size);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), tmp.data(), size);
	return sf::String::fromUtf8(tmp.begin(), tmp.end());
}
