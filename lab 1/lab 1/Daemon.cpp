#include "Daemon.h"

Daemon::Daemon(std::string& config_path)
{
	this->config_path = config_path;
	if (!readConfig(this->config_path, *this->config))
	{
		openlog("daemon", LOG_NOWAIT, LOG_USER);
		syslog(LOG_ERR, "Error while reading config");
		closelog();
	}
}

void Daemon::reloadConfig()
{

}

void Daemon::runDaemon()
{
	this->pid = fork();
	if (pid > 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		exit(EXIT_FAILURE);
	}

	umask(0);

	// Open system logs for the child process
	openlog("daemon", LOG_NOWAIT | LOG_PID, LOG_USER);
	syslog(LOG_NOTICE, "Successfully started daemon");

	// Generate a session ID for the child process
	this->sid = setsid();
	// Ensure a valid SID for the child process
	if (sid < 0)
	{
		// Log failure and exit
		syslog(LOG_ERR, "Could not generate session ID for child process");

		// If a new session ID could not be generated, we must terminate the child process
		// or it will be orphaned
		exit(EXIT_FAILURE);
	}

	// Change the current working directory to a directory guaranteed to exist
	if ((chdir("/")) < 0)
	{
		// Log failure and exit
		syslog(LOG_ERR, "Could not change working directory to /");

		// If our guaranteed directory does not exist, terminate the child process to ensure
		// the daemon has not been hijacked
		exit(EXIT_FAILURE);
	}

	// A daemon cannot use the terminal, so close standard file descriptors for security reasons
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while (!is_terminated)
	{
		for (unsigned i = 0; i < this->config->catalog_list.size())
			processDir(config->catalog_list[i]);
	}
}

void Daemon::terminateDaemon()
{

}

void Daemon::processDir(std::string dir_path)
{

}