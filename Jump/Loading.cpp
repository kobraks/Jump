#include "Loading.h"

#include "FrameRate.h"

using namespace jump;
using namespace system;

Loading& Loading::getInstance()
{
	static Loading load;
	return load;
}

Loading::Loading()
{
	value = 0;
	maxValue = 100;
	isWorking = false;
	thread = NULL;
	loadingStep = 10;
	this->rotation = 0.5f;
}

void Loading::initialize(sf::Font* font, int value, int maxValue, int loadingStep)
{
	if (this->isWorking) stop();

	this->value = value;
	this->maxValue = maxValue;
	this->loadingStep = loadingStep;
	this->text.setFont(*font);
	this->rotation = 0.5f;
}


Loading::~Loading()
{
	stop();
}

void Loading::start(sf::RenderWindow* window, bool showFPS, bool debug)
{
	if (thread != NULL)
	{
		stop();
	}

	isWorking = true;
	window->setActive(false);

	window->setView(window->getDefaultView());

	thread = new std::thread(&Loading::loading, this, window, debug, showFPS);
}

void Loading::loading(sf::RenderWindow* window, bool debug, bool showFPS)
{
	text.setCharacterSize(20U);
	text.setString("test");
	text.setPosition(0, window->getSize().y - text.getGlobalBounds().height * 4);
	
	wheel.setSize(sf::Vector2f(100, 100));
	wheel.setPosition(window->getSize().x / 2 - wheel.getSize().x / 2, window->getSize().y / 2 - wheel.getSize().y / 2);
	wheel.setOrigin(sf::Vector2f(50, 50));

	loadingBar.setSize(sf::Vector2f(0, text.getGlobalBounds().height));
	loadingBar.setPosition(0, window->getSize().y - text.getGlobalBounds().height * 2);

	if (showFPS) FrameRate::getInstance().initiate();
	while (isWorking)
	{
		wheel.rotate(rotation);


		float x = ((this->value * window->getSize().x) / 100);
		loadingBar.setSize(sf::Vector2f(x, loadingBar.getSize().y));

		window->clear();;

		text.setString(L"£adowanie " + std::to_wstring(this->value) + L"%");

		if (showFPS)
		{
			FrameRate::getInstance().update();
			FrameRate::getInstance().draw(*window);
		}
		this->draw(*window);

		window->display();

		if (maxValue <= value) isWorking = false;
	}

	window->setActive(false);
}

void Loading::stop()
{
	if (thread != NULL)
	{
		this->isWorking = false;
		thread->join();
		
		delete thread;

		thread = NULL;
	}
}

void Loading::add()
{
	this->value += loadingStep;
}

void Loading::add(const int& number)
{
	this->value += number;
}

void Loading::setLoadingStep(int step)
{
	this->loadingStep = step;
}

int Loading::getLoadingStep()
{
	return loadingStep;
}

void Loading::draw(sf::RenderWindow& window)
{
	//TODO
	window.draw(text);
	window.draw(wheel);
	window.draw(loadingBar);
}

void Loading::setMaxValue(int maxValue)
{
	this->maxValue = maxValue;
}

int Loading::getMaxValue()
{
	return this->maxValue;
}

void Loading::setValue(int value)
{
	this->value = value;
}

int Loading::getValue()
{
	return this->value;
}

void Loading::setFont(sf::Font* font)
{
	this->text.setFont(*font);
}

void Loading::loadTextureFromFile(std::map<std::string, std::string> name)
{
	textureWheel.loadFromFile(name["wheel"]);
	textureBar.loadFromFile(name["loadBar"]);

	wheel.setTexture(&textureWheel);
	loadingBar.setTexture(&textureBar);
}

Loading& Loading::operator+= (int number)
{
	this->value += number;
	return *this;
}

Loading& Loading::operator++()
{
	this->value += loadingStep;
	return *this;
}