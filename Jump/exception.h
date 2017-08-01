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

				virtual const char* what() const throw()
				{
					return message_.c_str();
				}

			private:
				std::string message_;
			};
		}
	}
}
