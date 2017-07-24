#include "FadeIn.h"


jump::system::animations::FadeIn::FadeIn(sf::Sprite& _sprite, float _speed) : Animation(_speed)
{
	sprite_ = new sf::Sprite(_sprite);
	texture_ = new sf::Texture(*_sprite.getTexture());
	sprite_->setTexture(*texture_);
	sprite_->setColor(sf::Color(255, 255, 255, 0));
	
	alpha_ = -0;
}

void jump::system::animations::FadeIn::update(sf::RenderWindow& _window)
{
	alpha_ += 1;

	if (alpha_ >= 0 && alpha_ <= 255)
		sprite_->setColor(sf::Color(255, 255, 255, alpha_));
	else if (alpha_ > 0)
		sprite_->setColor(sf::Color(255, 255, 255, 255));

	if (alpha_ >= 255) this->stop();
}

void jump::system::animations::FadeIn::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(*sprite_, _states);
}

jump::system::animations::FadeIn::~FadeIn()
{
	delete sprite_;
	delete texture_;
}
