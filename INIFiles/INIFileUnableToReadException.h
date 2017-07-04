#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileUnableToReadException : public INIFileException
		{
		public:

			INIFileUnableToReadException() : INIFileException(MSG_UNABLE_TO_READ_EXCEPTION)
			{
			}

			~INIFileUnableToReadException()
			{
			}
		};
	}
}

