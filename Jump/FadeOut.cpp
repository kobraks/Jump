#include "FadeOut.h"

using namespace jump;
using namespace system;
using namespace animations;

FadeOut::FadeOut(sf::Sprite& _sprite, float _speed) : FadeIn(_sprite, _speed)
{
	stage_ = 255;
}

void FadeOut::update(sf::RenderWindow& _window)
{
	stage_ -= 1;

	if (stage_ >= 0 && stage_ <= 255)
		sprite_->setColor(sf::Color(255, 255, 255, stage_));

	if (stage_ <= 0) this->stop();
}

void FadeOut::stage(sf::Uint16 _stage)
{
}
