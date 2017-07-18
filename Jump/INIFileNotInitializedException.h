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
				class IniFileNotInitializedException : public IniFileException
				{
				public:
					IniFileNotInitializedException() : IniFileException(MSG_NOT_INITIALIZED_EXCEPTION)
					{}
				};
			}
		}
	}
}
