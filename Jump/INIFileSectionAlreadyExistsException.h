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
				class IniFileSectionAlreadyExistsException : public IniFileException
				{
				public:
					IniFileSectionAlreadyExistsException() : IniFileException(MSG_SECTION_ALLREADY_EXISTS_EXCETPION)
					{ }
				};
			}
		}
	}
}