#include "Console.h"
#include "Log.h"

using namespace jump;
using namespace system;

Console& Console::getInstance()
{
	static Console instance;
	return instance;
}

Console::Console()
{
	_display = false;
	console.setSize(sf::Vector2f(800, 300));
	commandBar.setSize(sf::Vector2f(800, 20));

	console.setPosition(0, 300);
	commandBar.setPosition(0, 280);

	console.setFillColor(sf::Color(100, 100, 100, 100));
	commandBar.setFillColor(sf::Color(100, 100, 100, 150));
}


Console::~Console()
{
}

void Console::update()
{

}

void Console::draw(sf::RenderWindow& window)
{

}
