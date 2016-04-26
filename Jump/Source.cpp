#include <Windows.h>
#include <string>
#include <iostream>
#include <exception>

#include "Log.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	jump::Game *game;
	//try
	{
		FILELog::ReportingLevel() = logDEBUG4;
		FILELog::isEnabled() = true;
		FILE* log_fd;
		errno_t error;
		if ((error = fopen_s(&log_fd, "log.txt", "w")) != 0)
		{
			std::cout << "Cannot open file" << std::endl;
			throw error;
		}

		Output2FILE::Stream() = log_fd;

		FILE_LOG(logINFO) << "Starting Logging";

		std::string s;
		for (int i = 0; i < argc; i++)
		{
			s +=  std::to_string(i + 1);
			s += argv[i];
			if (i < argc-1) s += "\n";
		}

		FILE_LOG(logINFO) << "Program is runing with " + std::to_string(argc) + " argument. "+ s;
		systemInformation();

		game = new jump::Game;

		game->runGame();
	}
	//catch (...)
	{

	}

	delete game;
	return EXIT_SUCCESS;
}