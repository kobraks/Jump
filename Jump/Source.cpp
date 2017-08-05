#include <iostream>
#include <exception>
#include <memory>
#include <thread>

#include "Game.h"

int main(int argc, char* argv[])
{
	jump::Game* game = nullptr;

	try
	{
		game = new jump::Game();
		game->run_game();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	catch (...)
	{

	}
	delete game;

	return EXIT_SUCCESS;
}