#include "AnimationHandler.h"

using namespace jump;
using namespace system;

AnimationHandler& AnimationHandler::getInstance()
{
	static AnimationHandler animation;
	return animation;
}

AnimationHandler::AnimationHandler()
{
}

AnimationHandler& AnimationHandler::addAnimation(Animation* animation, float sleep)
{
	animation->sleep(sleep);

	_items.push_back(std::shared_ptr<Animation>(animation));

	return *this;
}

AnimationHandler& AnimationHandler::addAnimation(Animation* animation, bool pause)
{
	if (pause) animation->pause();
	_items.push_back(std::shared_ptr<Animation>(animation));

	return *this;
}

AnimationHandler& AnimationHandler::addAnimation(Animation* animation, Animation* runAf)
{
	std::shared_ptr<Animation> tmp(animation);
	std::shared_ptr<Animation> tmpA(runAf);

	if (runAf) animation->runAfterEnd(tmpA);
	this->addAnimation(tmpA);
	_items.push_back(tmp);

	return *this;
}

AnimationHandler& AnimationHandler::addAnimation(std::shared_ptr<Animation> animation, float sleep)
{
	animation->sleep(sleep);

	_items.push_back(animation);

	return *this;
}

AnimationHandler& AnimationHandler::addAnimation(std::shared_ptr<Animation> animation, bool pause)
{
	if (pause) animation->pause();
	_items.push_back(animation);

	return *this;
}

AnimationHandler& AnimationHandler::addAnimation(std::shared_ptr<Animation> animation, std::shared_ptr<Animation> runAfterAnimation)
{
	if (runAfterAnimation) animation->runAfterEnd(runAfterAnimation);
	this->addAnimation(runAfterAnimation);

	_items.push_back(animation);

	return *this;
}

AnimationHandler& AnimationHandler::deleteAnimation(int index)
{
	if (_items.empty()) return *this;
	if (index >= 0 && index < _items.size()) _items.erase(_items.begin() + index);

	return *this;
}

void AnimationHandler::update()
{
	if (_items.empty()) return;

	for (int i = 0; i < _items.size(); i++)
	{
		auto element = _items[i];

		if (element->isRunning())
		{
			if (!element->isPaused())
			{
				if (element->_speed <= element->_clock->getElapsedTime().asSeconds())
				{
					element->update();
					element->_clock->restart();
				}
			}
		}
		else
		{
			_items.erase(_items.begin() + i);

			i--;
		}
	}
}

void AnimationHandler::draw(sf::RenderWindow& window)
{
	if (_items.empty()) return;

	for (auto element : _items)
	{
		element->draw(window);
	}
}

AnimationHandler& AnimationHandler::deleteAll()
{
	if (_items.empty()) return *this;

	_items.clear();

	return *this;
}

std::vector<std::shared_ptr<Animation>> AnimationHandler::getAnimations()
{
	return _items;
}

AnimationHandler::~AnimationHandler()
{
	this->deleteAll();
}