#include "Config.h"

inline bool isNumber(std::string& line)
{
	return !line.empty() && (line.find_first_not_of("0123456789") == line.npos);
}

bool readConfig(std::string& config_path, Config& config)
{
	std::ifstream file_stream(config_path);
	std::string line;

	if (!file_stream.is_open())
		return false;

	unsigned line_count = 0;

	while (line_count != 3)
	{
		file_stream >> line;
		if (!line.empty())
			continue;
		else
		{
			if (isNumber(line))
			{
				config.REPEAT_TIME = stoul(line);
				line_count++;
			}
			else if (config.catalog_list.size() < 3)
			{
				config.catalog_list.push_back(line);
				line_count++;
			}
			else
				return false;
		}
	}

	file_stream.close();
}