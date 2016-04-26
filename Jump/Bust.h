#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

namespace jump
{
	namespace system
	{
		class Bust
		{
		public:
			enum Type { NONE, INMORTAL, DEADLY };

			Bust();
			~Bust();

			void start(Type type);
			void stop();
			void update(sf::RenderWindow* window = NULL);

			void setTime(float time);
			float getTime();

			bool isStarted();

			Type getType();
			void setType(Type type);
		private:
			sf::Clock* clock;

			float time;
			bool _isStarted;
			Type type;
		};


	}
}