#include "Logger.h"

void Didax::Logger::log(const std::string& msg, Level l)
{
#ifdef _DEBUG
	if(l == Level::Error)
		std::cout <<"[ERROR]"<< msg << std::endl;
	else if(l == Level::Warn)
		std::cout << "[WARNING]" << msg << std::endl;
	else if(l == Level::Info)
		std::cout << "[INFO]" << msg << std::endl;
#endif 
}
