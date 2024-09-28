#include <string>
#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>

#include "Config.h"

class Daemon
{
public:
	static Daemon& getDaemon(std::string& config_path)
	{
		static Daemon instance(config_path);
		return instance;
	}

	void reloadConfig();
	void terminateDaemon();
	void runDaemon();

	Daemon(Daemon&&) = delete;
	Daemon& operator=(Daemon&&) = delete;
	Daemon(Daemon const&) = delete;
	Daemon& operator=(Daemon const&) = delete;

private:
	Daemon(std::string& config_path);

	void processDir(std::string dir_path);

	std::string config_path;
	Config* config;
	std::string PID_PATH;

	pid_t pid;
	pid_t sid;

	bool is_terminated = false;

	static inline const std::string _daemonName = "deleter";
	static inline const fs::path _pidPath = fs::path("/var/run/" + _daemonName + ".pid");
	static inline const int _sleepTime = 20;
	const fs::path _configPath;
};