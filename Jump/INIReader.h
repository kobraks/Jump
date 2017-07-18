#pragma once
#include <string>
#include <istream>


#include "INIFile.h"

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniReader
			{
			public:
				IniReader(IniFile* _ini, const std::string& _file_name);
				IniReader(IniFile* _ini, std::istream& _input);

				~IniReader();
			};
		}
	}
}

