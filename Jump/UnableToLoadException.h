#pragma once
#include "exception.h"
#include "MSGExceptions.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class UnableToLoadException : public Exception
			{
			public:
				UnableToLoadException(const std::string& _message) : Exception(MSG_UNABLE_TO_LOAD + _message)
				{
					
				}
			};
		}
	}
}
