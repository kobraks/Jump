#pragma once
#include "MSGExceptions.h"
#include "Exception.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class FontDoesNotExistException : public Exception
			{
			public:
				FontDoesNotExistException() : Exception(MSG_FONT_DOES_NOT_EXIST_EXCPETION)
				{
					
				}
			};
		}
	}
}