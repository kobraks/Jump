#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileSectionDoesNotExistsException : public INIFileException
		{
		public:

			INIFileSectionDoesNotExistsException() : INIFileException(MSG_SECITON_NOT_EXIST_EXCEPTION)
			{
			}
		};
	}
}