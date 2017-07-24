#include "FadeOut.h"

using namespace jump;
using namespace system;
using namespace animations;

FadeOut::FadeOut(sf::Sprite& _sprite, float _speed) : FadeIn(_sprite, _speed)
{
	alpha_ = 255;
}

void FadeOut::update(sf::RenderWindow& _window)
{
	alpha_ -= 1;

	if (alpha_ >= 0 && alpha_ <= 255)
		sprite_->setColor(sf::Color(255, 255, 255, alpha_));
	else if (alpha_ < 0)
		sprite_->setColor(sf::Color(255, 255, 255, 0));

	if (alpha_ <= 0) this->stop();
}