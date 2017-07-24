#pragma once
#include "UnableToLoadException.h"
#include "MSGExceptions.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class UnableToLoadFontException : public UnableToLoadException
			{
			public:
				UnableToLoadFontException(const std::string& _font_name) : UnableToLoadException(MSG_UNABLE_TO_LOAD + MSG_UNABLE_TO_LOAD_FONT + _font_name)
				{}
			};
		}
	}
}

