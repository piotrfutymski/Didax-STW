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
	catch (std::exception&) {
		Logger::log("Unable to open json file: " + filename);
	}
	return res;
}
