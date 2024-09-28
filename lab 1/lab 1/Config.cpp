#include "Config.h"

bool readConfig(std::string& config_path, Config& config)
{
	std::ifstream file_stream(config_path);
	std::string line;

	if (!file_stream.is_open())
		return false;

	while (std::getline(file_stream, line))
	{
		std::pair<fs::path, unsigned> path_and_time;
		if (!line.empty())
			continue;
		else if (divideString(line, path_and_time))
		{
			config.catalog_list.push_back(path_and_time);
		}
	}

	file_stream.close();
	return true;
}

bool divideString(std::string& line, std::pair<fs::path, unsigned>& pair)
{
	if (line.find(" ") == line.rfind(" "))
	{
		std::string dir = line.substr(0, line.find(" "));
		unsigned refresh_time = stoul(line.substr(line.find(" ")));
		pair.first = dir;
		pair.second = refresh_time;
		return true;
	}
	else
		return false;
}