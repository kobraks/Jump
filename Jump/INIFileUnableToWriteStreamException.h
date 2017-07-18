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
				class IniFileUnableToWriteStreamException : public IniFileException
				{
				public:
					IniFileUnableToWriteStreamException() : IniFileException(MSG_UNABLE_TO_WRITE_STREAM_EXCEPTION)
					{}
				};
			}
		}
	}
}