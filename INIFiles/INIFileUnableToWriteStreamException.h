#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileUnableToWriteStreamException : public INIFileException
		{
		public:
			INIFileUnableToWriteStreamException() : INIFileException(MSG_UNABLE_TO_WRITE_STREAM_EXCEPTION)
			{}
		};
	}
}