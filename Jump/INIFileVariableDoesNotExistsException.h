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
				class IniFileVariableDoesNotExistsException : public IniFileException
				{
				public:

					IniFileVariableDoesNotExistsException() : IniFileException(MSG_VARIABLE_NOT_EXSITS_EXCEPTION)
					{
					}
				};
			}
		}
	}
}

