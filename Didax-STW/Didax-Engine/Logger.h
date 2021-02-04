#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <exception>

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
	};

}