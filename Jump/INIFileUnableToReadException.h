#pragma once
#include "IniFileException.h"
#include "MSGExceptions.h"


namespace jump
{
	namespace system
	{
		namespace ini
		{
			namespace exception
			{
				class IniFileUnableToReadException : public IniFileException
				{
				public:

					IniFileUnableToReadException() : IniFileException(MSG_UNABLE_TO_READ_EXCEPTION)
					{
					}

					~IniFileUnableToReadException()
					{
					}
				};
			}
		}
	}
}

