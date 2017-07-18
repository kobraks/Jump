#include "FontCoinatiner.h"

#include <algorithm>

jump::system::FontCointainer::FontCointainer()
{
	
}

sf::Font* jump::system::FontCointainer::find(std::string _name)
{
	auto font = fonts_.find(_name);

	if (font == fonts_.end())
		return nullptr;
	else
		return font->second;
}

sf::Font* jump::system::FontCointainer::get_font(std::string _name)
{
	auto font = get_instance()->find(_name);

	if (font)
		return font;
	else
		throw std::exception();
}

jump::system::FontCointainer* jump::system::FontCointainer::add_font(std::string _name, sf::Font* _font)
{
	if (_font)
		get_instance()->fonts_[_name] = _font;
	else
		throw std::exception();
}

jump::system::FontCointainer::~FontCointainer()
{
	for (auto font : fonts_)
	{
		delete font.second;
	}
}


