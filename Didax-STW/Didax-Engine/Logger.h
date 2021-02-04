#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include<fstream>
#include <nlohmann/json.hpp>

namespace Didax
{
	class Logger
	{
	public:
		enum class Level {
			Info, Warn, Error
		};

		static void log(const std::string& msg, Level = Level::Error);

		static void close();

		static std::ofstream file;
	};

}