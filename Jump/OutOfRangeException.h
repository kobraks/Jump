#pragma once
#include "MSGExceptions.h"
#include "Exception.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class OutOfRangeException : public Exception
			{
			public:
				OutOfRangeException() : Exception(MSG_OUT_OF_RANGE_EXCEPTION)
				{  }
			};
		}
	}
}