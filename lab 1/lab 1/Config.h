#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

struct Config
{
	std::vector<std::pair<fs::path, unsigned>> catalog_list;
	unsigned REFRESH_TIME = 20;
};

bool readConfig(std::string& config_path, Config& config);