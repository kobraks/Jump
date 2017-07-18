#pragma once
#include <vector>

#include "IniToken.h"
#include "IniSection.h"

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniParser
			{
			public:
				IniParser(std::vector<IniToken*>& _tokens);

				std::vector<ini::IniSection*> parse();
			private:
				std::vector<IniToken*> tokens_;
			};
		}
	}
}