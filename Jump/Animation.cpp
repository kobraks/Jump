#include "Animation.h"

#include <exception>

#include "Log.h"

using namespace jump;
using namespace system;

Animation::Animation()
{
	initialize(animations::speed::MEDIUM);
}

Animation::Animation(float speed)
{
	initialize(speed);
}

void Animation::initialize(float speed)
{
	_animation = NULL;
	_pauseClock = NULL;
	_isRun = true;
	_isPaused = false;
	_pauseTime = 0;
	_clock = new sf::Clock;
	_speed = speed;
}

Animation::~Animation()
{
	delete _pauseClock;

	if (_animation)
	{
		_animation->pause();
	}
}

void Animation::updatePauseTimer()
{
	if (!_pauseClock) return;

	if (_pauseClock->getElapsedTime().asSeconds() >= this->_pauseTime) this->_isPaused = false;
}

bool Animation::isRunning()
{
	return _isRun;
}

bool Animation::isPaused()
{
	return _isPaused;
}

void Animation::sleep(float time)
{
	if (time > 0)
	{
		this->_isPaused = true;
		this->_pauseClock = new sf::Clock();
		this->_pauseTime = time;
	}
}

void Animation::pause()
{
	if (this->_isPaused)
	{
		if (_pauseClock)
		{
			delete _pauseClock;
			_pauseTime = 0;
		}

		this->_isPaused = false;
	}

	else
	{
		this->_isPaused = true;
	}
}

void Animation::stop()
{
	this->_isRun = false;
}

void Animation::runAfterEnd(std::shared_ptr<Animation> animation)
{
	_animation = std::shared_ptr<Animation>(animation);
	animation->pause();
}