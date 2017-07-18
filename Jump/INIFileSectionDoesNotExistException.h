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
				class IniFileSectionDoesNotExistsException : public IniFileException
				{
				public:

					IniFileSectionDoesNotExistsException() : IniFileException(MSG_SECITON_NOT_EXIST_EXCEPTION)
					{
					}
				};
			}
		}
	}
}