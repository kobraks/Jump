#include "Configuration.h"
#include "INIFiles.hpp"

using namespace jump;
using namespace system;

Configuration::Configuration()
{
}


Configuration::~Configuration()
{
	debugFont = NULL;

	delete debugFont;
}

void Configuration::loadFromFile(std::wstring name)
{
	this->name = name;

	ini::INIFiles ini(name);

	fontPath = ini.read("fonts", "fonts Path", (std::string)"Data/Fonts/");
	fontNames["title"] = ini.read("fonts", "title font", "FRADM.ttf");
	fontNames["options"] = ini.read("fonts", "options font", (std::string)"framd.ttf");
	fontNames["author"] = ini.read("fonts", "author font", (std::string)"FRADM.ttf");
	fontNames["debug"] = ini.read("fonts", "debug font", (std::string)"consola.ttf");
	
	texturesPath = ini.read("textures", "textures Path", "Data/Textures/");
	playerTextures = ini.read("textures", "player textures", "Player.png");

	xmlFiles = ini.read("textures", "path to xml files", "Data/XML/");
	
	pathToInterface = ini.read("textures", "interface textures path", "Data/Interface/");

	loadingTextures["wheel"] = pathToInterface + ini.read("textures", "loading wheel", "wheel.png");
	loadingTextures["loadBar"] = pathToInterface + ini.read("textures", "loading bar", "loadbar.png");
	itemsTextures = ini.read("textures", "items", "items.png");

	debug = ini.read("general", "dewelop mode", true);
	width = ini.read("general", "width", 800);
	height = ini.read("general", "height", 600);

	startMap = ini.read("general", "starting map", L"example.txt");

	showFPS = ini.read("general", "show fps", true);

	up = static_cast<sf::Keyboard::Key>(static_cast<int>(ini.read("general", "Up", 'W')));
	down = static_cast<sf::Keyboard::Key>(static_cast<int>(ini.read("general", "Down", 'S')));
	left = static_cast<sf::Keyboard::Key>(static_cast<int>(ini.read("general", "Left", 'A')));
	right = static_cast<sf::Keyboard::Key>(static_cast<int>(ini.read("general", "Right", 'D')));

	hudTextures = "hud.png";

	dataFile = ini.read("general", "data file", "Data");

	maxClouds = 5;

	if (!ini.isOpened()) save();
}

void Configuration::save()
{
	ini::INIFiles ini(name);
	if (!ini.isOpened()) return;

	ini.write("general", "width", width);
	ini.write("general", "height", height);

	ini.write("general", "starting map", startMap);

	ini.write("general", "Up", static_cast<char>(up));
	ini.write("general", "Down", static_cast<char>(down));
	ini.write("general", "Left", static_cast<char>(left));
	ini.write("general", "Right", static_cast<char>(right));

	ini.write("general", "data file", dataFile);

	ini.write("fonts", "fonts Path", this->fontPath);
	ini.write("fonts", "title font", fontNames["title"]);
	ini.write("fonts", "options font", fontNames["options"]);
	ini.write("fonts", "author font", fontNames["author"]);
	ini.write("fonts", "debug font", fontNames["debug"]);
}