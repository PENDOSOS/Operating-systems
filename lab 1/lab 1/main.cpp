#include "Daemon.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Wrong count of arguments! Programm needs only path to the logger config!" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        Daemon& daemon = Daemon::getDaemon(std::string(argv[1]));
    }

	return 0;
}
