#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileUnableToWriteFile : public INIFileException
		{
		public:
			INIFileUnableToWriteFile() : INIFileException(MSG_UNABLE_TO_WRITE_EXCEPTION)
			{
			}
		};
	}
}