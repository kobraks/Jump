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
				class IniFileUnableToWriteFile : public IniFileException
				{
				public:
					IniFileUnableToWriteFile() : IniFileException(MSG_UNABLE_TO_WRITE_EXCEPTION)
					{
					}
				};
			}
		}
	}
}