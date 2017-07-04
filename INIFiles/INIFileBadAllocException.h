#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileBadAllocException : public INIFileException
		{
		public:
			INIFileBadAllocException() : INIFileException(MSG_BAD_ALLOC_EXCEPTION)
			{}
		};

	}
}