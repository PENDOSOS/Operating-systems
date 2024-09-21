#pragma once

#include <string>
#include <vector>
#include <fstream>

struct Config
{
	std::vector<std::pair<std::string&, unsigned>> catalog_list;
	unsigned REFRESH_TIME = 20;
};

bool readConfig(std::string& config_path, Config& config);