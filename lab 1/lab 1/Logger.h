#pragma once

#include <iostream>

#include "Config.h"

class Logger
{
public:
	Logger() = default;
	Logger() = delete;
	Logger(Logger const&) = delete;
	Logger& operator=(Logger const&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;
	
	bool log();

private:
	std::string generateLog();

	std::string log_file = "logs.log";
};
