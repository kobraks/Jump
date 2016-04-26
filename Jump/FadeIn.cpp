#include "FadeIn.h"

using namespace jump;
using namespace system;
using namespace animations;

FadeIn::FadeIn(sf::Sprite& sprite, float speed)
{
	initialize(speed);

	this->_sprite = new sf::Sprite(sprite);
	_texture = new sf::Texture(*sprite.getTexture());
	_sprite->setTexture(*_texture);
	_sprite->setColor(sf::Color(255, 255, 255, 0));
	
	_alpha = -0;
}

void FadeIn::update()
{
	_alpha += 1;

	if (_alpha >= 0 && _alpha <= 255)
		_sprite->setColor(sf::Color(255, 255, 255, _alpha));
	else if (_alpha > 0)
		_sprite->setColor(sf::Color(255, 255, 255, 255));

	if (_alpha >= 255) this->stop();
}

void FadeIn::draw(sf::RenderWindow& window)
{
	window.draw(*_sprite);
}

FadeIn::~FadeIn()
{
	delete _sprite;
	delete _texture;
}
