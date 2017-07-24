#include "Animation.h"

#include <exception>

jump::system::Animation::Animation(Animation* _animation): animation_(_animation), pause_time_(0), speed_(animations::speed::MEDIUM),
run_(false), paused_(false), pause_clock_(nullptr), clock_(new sf::Clock)
{
}

jump::system::Animation::Animation(float _speed, Animation* _animation) : Animation(_animation)
{
	speed_ = _speed;
}

jump::system::Animation::~Animation()
{

	delete pause_clock_;
	delete clock_;

	if (animation_)
		animation_->pause();
}

void jump::system::Animation::update_pause_timer()
{
	if (!pause_clock_) return;

	if (pause_clock_->getElapsedTime().asSeconds() >= pause_time_)
	{
		delete pause_clock_;
		pause();
	}
}

bool jump::system::Animation::is_running() const
{
	return run_;
}

bool jump::system::Animation::is_paused() const
{
	return paused_;
}


void jump::system::Animation::sleep(float _time)
{
	if (_time > 0)
	{
		paused_ = true;
		if (pause_clock_)
			pause_clock_->restart();
		else
			pause_clock_ = new sf::Clock();

		pause_time_ = _time;
	}
}

void jump::system::Animation::pause()
{
	if (paused_)
	{
		if (pause_clock_)
		{
			delete pause_clock_;
			pause_time_ = 0;
		}

		paused_ = false;
	}

	else
	{
		paused_ = true;
	}
}

void jump::system::Animation::stop()
{
	run_ = false;
}

void jump::system::Animation::start()
{
	run_ = true;
}

void jump::system::Animation::run_after_end(Animation* _animation)
{
	animation_ = _animation;
	animation_->pause();
}

void jump::system::Animation::update_handler(sf::RenderWindow& _window)
{
	if (run_)
	{
		if (paused_)
			update_pause_timer();
		else if (speed_ <= clock_->getElapsedTime().asSeconds())
		{
			update(_window);
			clock_->restart();
		}
	}
}