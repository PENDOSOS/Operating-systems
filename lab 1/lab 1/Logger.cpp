#include "Logger.h"

bool Logger::log()
{
	std::ofstream log_stream(this->log_file);
	if (!log_stream.is_open())
		return false;
	else
	{
		log_stream << this->generateLog();
		return true;
	}
}