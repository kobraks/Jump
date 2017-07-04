#pragma once
#include <exception>
namespace ini
{
	namespace exception
	{
		class INIFileException : public std::exception
		{
		public:

			INIFileException(const char* _message) : message_(_message)
			{
			}

			virtual const char* what() const noexcept
			{
				return message_;
			}

		private:
			const char* message_;
		};
	}
}

