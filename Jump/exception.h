#pragma once
#include <exception>
#include <string>
#include "Log.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class Exception : public std::exception
			{
			public:
				explicit Exception(const std::string& message) : message_(message)
				{
					Log::write_error("", message);
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
