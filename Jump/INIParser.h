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
				std::vector<IniToken*>::iterator it_;

				IniSection* get_section();
				IniVariable* get_variable();

				bool get_variable_name(std::string& _var_name);
				bool get_variable_value(std::string& _var_value);
				void read_comment();
			};
		}
	}
}