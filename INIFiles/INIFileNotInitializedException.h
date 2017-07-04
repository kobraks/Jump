#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileNotInitializedException : public INIFileException
		{
		public:
			INIFileNotInitializedException() : INIFileException(MSG_NOT_INITIALIZED_EXCEPTION)
			{}
		};
	}
}

