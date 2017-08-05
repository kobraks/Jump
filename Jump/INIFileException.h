#pragma once
#include <exception>
#include <string>

namespace jump
{
	namespace system
	{
		namespace ini
		{
			namespace exception
			{
				class IniFileException : public std::exception
				{
				public:

					explicit IniFileException(const std::string& _message) : message_(_message)
					{
					}

					const char* what() const throw() override
					{
						return message_.c_str();
					}

				private:
					std::string message_;
				};
			}
		}
	}
}

