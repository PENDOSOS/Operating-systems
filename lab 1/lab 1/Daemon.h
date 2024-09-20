class Daemon
{
public:
	static Daemon& getDaemon()
	{
		static Daemon instance;
		return instance;
	}

	void reloadConfig();
	void terminateDaeon();

	Daemon(Daemon&&) = delete;
	Daemon& operator=(Daemon&&) = delete;
	Daemon(Daemon const&) = delete;
	Daemon& operator=(Daemon const&) = delete;

private:
	Daemon()
	{}
};