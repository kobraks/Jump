#pragma once
#include <string>
#include <ostream>


#include "INIFile.h"

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniWriter
			{
			public:
				IniWriter(IniFile* _ini, const std::string& _file_name, const bool& _override = true);
				IniWriter(IniFile* _ini, std::ostream& _stream);
				~IniWriter();
			};
		}
	}
}
