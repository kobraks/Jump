#include "AnimationHandler.h"

#include <algorithm>

jump::system::AnimationHandler* jump::system::AnimationHandler::get_instance()
{
	static AnimationHandler animation;
	return &animation;
}

jump::system::AnimationHandler::AnimationHandler()
{
}

jump::system::AnimationHandler* jump::system::AnimationHandler::add(Animation* _animation)
{
	auto instance = get_instance();

	if (_animation)
		instance->animations_.push_back(_animation);
	else
		throw std::exception();

	return instance;
}

jump::system::AnimationHandler* jump::system::AnimationHandler::remove_animation(const unsigned int& _index)
{
	auto instance = get_instance();

	if (instance->animations_.empty())
		throw std::exception();

	if (_index >= 0 && _index < instance->animations_.size())
		instance->animations_.erase(instance->animations_.begin() + _index);
	else
		throw std::exception();

	return instance;
}

class jump::system::AnimationHandler* jump::system::AnimationHandler::remove_animation(Animation* _animation)
{
	auto instance = get_instance();


}


jump::system::AnimationHandler* jump::system::AnimationHandler::update(sf::RenderWindow& _window)
{
	auto instance = get_instance();

	for (size_t i = 0; i < instance->animations_.size(); i++)
	{
		auto animation = instance->animations_[i];

		if (animation->is_running())
			animation->update_handler(_window);
		else
		{
			remove_animation(i);

			i--;
		}
	}

	return instance;
}

jump::system::AnimationHandler* jump::system::AnimationHandler::draw(sf::RenderWindow& window)
{
	auto instance = get_instance();

	for (auto animation : instance->animations_)
		window.draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(animation)));
	
	return instance;
}

jump::system::AnimationHandler* jump::system::AnimationHandler::clear()
{
	auto instance = get_instance();

	for (auto animation : instance->animations_)
		delete animation;

	instance->animations_.clear();

	return instance;
}

std::vector<jump::system::Animation*> jump::system::AnimationHandler::get_animations()
{
	return get_instance()->animations_;
}

jump::system::AnimationHandler::~AnimationHandler()
{
	clear();
}