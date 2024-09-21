#include <string>
#include <unistd.h>

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

	std::string config_path;
	std::string PID_PATH;
	unsigned REPEAT_TIME = 20;

};