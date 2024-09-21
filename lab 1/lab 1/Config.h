#pragma once

#include <string>
#include <vector>
#include <fstream>

struct Config
{
	std::vector<std::string> catalog_list;
	unsigned REPEAT_TIME;
};

bool readConfig(std::string& config_path, Config& config);