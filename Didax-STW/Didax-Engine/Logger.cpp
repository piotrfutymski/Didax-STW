#include "Logger.h"

void Didax::Logger::log(const std::string& msg, Level l)
{
#ifdef _DEBUG
	if (l == Level::Error)
	{
		std::cout << "[ERROR]" << msg << std::endl;
		file << "[ERROR]" << msg << std::endl;
	}		
	else if (l == Level::Warn)
	{
		std::cout << "[WARNING]" << msg << std::endl;
		file << "[WARNING]" << msg << std::endl;
	}
	else if (l == Level::Info)
	{
		std::cout << "[INFO]" << msg << std::endl;
		file << "[INFO]" << msg << std::endl;
	}		
#endif 
}

void Didax::Logger::close()
{
	file.close();
}

std::ofstream Didax::Logger::file{"log.txt",std::ios::out};
