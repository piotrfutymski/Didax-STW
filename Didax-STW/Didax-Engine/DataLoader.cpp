#include "DataLoader.h"

nlohmann::json Didax::DataLoader::loadJsonFromFile(const std::string& filename)
{
	nlohmann::json res;
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
#ifdef _DEBUG
		std::cout << "Unable to open file: " << filename << std::endl;
#endif // _DEBUG
		throw new std::exception("Data can't be loaded");
	}
	try {
		stream >> res;
	}
	catch (std::exception&) {
#ifdef _DEBUG
		std::cout << "Unable to read json from file: " << filename << std::endl;
#endif 
		throw new std::exception("Data can't be loaded");
	}
	return res;
}
