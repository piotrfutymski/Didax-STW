#include "DataLoader.h"

nlohmann::json Didax::DataLoader::loadJsonFromFile(const std::string& filename)
{
	nlohmann::json res;
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		Logger::log("Unable to open json file: " + filename);
		throw new std::exception("Data can't be loaded");
	}
	try {
		stream >> res;
	}
	catch (std::exception&) {
		Logger::log("Unable to open json file: " + filename);
		throw new std::exception("Data can't be loaded");
	}
	return res;
}
