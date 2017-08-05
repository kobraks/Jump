#pragma once
#include <exception>
#include <string>

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class Exception : public std::exception
			{
			public:
				explicit Exception(const std::string& _message) : message_(_message)
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
