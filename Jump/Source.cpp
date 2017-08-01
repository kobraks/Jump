#include <iostream>
#include <exception>
#include <memory>

#include "Game.h"

int main(int argc, char* argv[])
{
	try
	{
		auto game = std::make_unique<jump::Game>();

		game->run_game();
	}
	catch (std::bad_alloc)
	{
		
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		system("pause");

	}
	catch (...)
	{

	}

	return EXIT_SUCCESS;
}