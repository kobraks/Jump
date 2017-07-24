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

					IniFileException(const std::string& _message) : message_(_message)
					{
					}

					virtual const char* what() const noexcept
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
