#pragma once
#include "MSGExceptions.h"
#include "Exception.h"

namespace jump
{
	namespace system
	{
		namespace exception
		{
			class NotInicializedException : public Exception
			{
			public:
				NotInicializedException() : Exception(MSG_NOT_INITIALIZED_EXCEPTION) 
				{  }
			};
		}
	}
}