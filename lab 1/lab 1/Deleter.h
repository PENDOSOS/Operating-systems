#pragma once

#include <filesystem>
#include <algorithm>
#include <sys/syslog.h>
#include <numeric>
#include <functional>

namespace fs = std::filesystem;

class Deleter
{
public:
	static void deleteDirs(std::vector<std::pair<std::string, int>> const& dirs);
private:
	static void deleteDir(std::pair<std::string, int> const& dir);
	static void checkForSubdir(const fs::path& current_dir, int current_level, int current_depth);

	static const int _rootDepth = 0;
};