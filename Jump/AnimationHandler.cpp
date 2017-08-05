#include "AnimationHandler.h"

#include <algorithm>
#include "OutOfRangeException.h"
#include "NotInicializedException.h"

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
	{
		if (!contains(_animation))
			instance->animations_.push_back(_animation);
	}
	else
		throw exception::NotInicializedException();

	return instance;
}

jump::system::AnimationHandler* jump::system::AnimationHandler::remove_animation(const size_t& _index)
{
	auto instance = get_instance();
	auto& animations = instance->animations_;

	if (_index >= 0 && _index < animations.size())
	{
		delete animations[_index];
		animations.erase(animations.begin() + _index);
	}
	else
		throw exception::OutOfRangeException();

	return instance;
}

jump::system::AnimationHandler* jump::system::AnimationHandler::remove_animation(Animation* _animation)
{
	auto instance = get_instance();

	if (!_animation)
		throw exception::NotInicializedException();

	auto find = std::find(instance->animations_.begin(), instance->animations_.end(), _animation);
	if (instance->animations_.end() != find)
	{
		delete *find;

		instance->animations_.erase(find);
	}
	else
		throw std::exception(); //TODO exception name

	return instance;
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
	{
		animation->animation_ = nullptr;
		delete animation;
	}

	instance->animations_.clear();

	return instance;
}

bool jump::system::AnimationHandler::contains(Animation* _animation)
{
	auto instance = get_instance();

	return std::find(instance->animations_.begin(), instance->animations_.end(), _animation) != instance->animations_.end();
}

std::vector<jump::system::Animation*> jump::system::AnimationHandler::get_animations()
{
	return get_instance()->animations_;
}

jump::system::AnimationHandler::~AnimationHandler()
{
	clear();
}