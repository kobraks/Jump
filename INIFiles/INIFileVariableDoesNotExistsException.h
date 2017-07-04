#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{ 
		class INIFileVariableDoesNotExistsException : public INIFileException
		{
		public:

			INIFileVariableDoesNotExistsException() : INIFileException(MSG_VARIABLE_NOT_EXSITS_EXCEPTION)
			{
			}
		};
	}
}

