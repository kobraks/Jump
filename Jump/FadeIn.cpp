#include "FadeIn.h"


jump::system::animations::FadeIn::FadeIn(sf::Sprite& _sprite, float _speed) : Animation(255, _speed)
{
	sprite_ = &_sprite;
	sprite_->setColor(sf::Color(255, 255, 255, 0));
	
	stage_ = -0;
}

void jump::system::animations::FadeIn::update(sf::RenderWindow& _window)
{
	stage_ += 1;

	if (stage_ >= 0 && stage_ <= 255)
		sprite_->setColor(sf::Color(255, 255, 255, stage_));
	else
		sprite_->setColor(sf::Color(255, 255, 255, 255));

	if (stage_ >= 255) this->stop();
}

void jump::system::animations::FadeIn::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(*sprite_, _states);
}

jump::system::animations::FadeIn::~FadeIn()
{
}
