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
				class IniFileBadAllocException : public IniFileException
				{
				public:
					IniFileBadAllocException() : IniFileException(MSG_BAD_ALLOC_EXCEPTION)
					{}
				};

			}
		}
	}
}