#pragma once
#include <string>
#include "MSGExceptions.h"
#include "Exception.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class UnableToOpenFileException : public Exception
			{
			public:
				explicit UnableToOpenFileException(std::string file_name) : Exception(MSG_UNABLE_TO_OPEN_FILE_EXCEPTION + file_name)
				{
				}
			};
		}
	}
}