#include "FadeOut.h"

using namespace jump;
using namespace system;
using namespace animations;

FadeOut::FadeOut(sf::Sprite& sprite, float speed) : FadeIn(sprite, speed)
{
	this->_alpha = 255;
}

void FadeOut::update()
{
	_alpha -= 1;

	if (_alpha >= 0 && _alpha <= 255)
		_sprite->setColor(sf::Color(255, 255, 255, _alpha));
	else if (_alpha < 0)
		_sprite->setColor(sf::Color(255, 255, 255, 0));

	if (_alpha <= 0) this->stop();
}