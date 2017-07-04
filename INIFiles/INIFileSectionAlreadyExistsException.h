#pragma once
#include "INIFileException.h"
#include "MSGExceptions.h"
#include "Exports.hpp"

namespace ini
{
	namespace exception
	{
		class INIFileSectionAlreadyExistsException : public INIFileException
		{
		public:
			INIFileSectionAlreadyExistsException() : INIFileException(MSG_SECTION_ALLREADY_EXISTS_EXCETPION)
			{ }
		};
	}
}