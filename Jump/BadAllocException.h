#pragma once

#include "Exception.h"
#include "MSGExceptions.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class BadAllocException : public Exception
			{
			public:
				BadAllocException() : Exception(MSG_BAD_ALLOC_EXCEPTION)
				{}
			};
		}
	}
}