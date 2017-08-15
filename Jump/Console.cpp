#include "Console.h"



jump::system::Console::Console()
{
}


jump::system::Console::~Console()
{
}

jump::system::Console* jump::system::Console::get_instance()
{
	static Console instance;
	return &instance;
}

void jump::system::Console::draw(const char* title, const bool* const p_open)
{
}
