#pragma once

#include <string>
#include <vector>
#include <initializer_list>


#include "IniSection.h"

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniFile
			{
			public:
				IniFile();
				IniFile(const std::initializer_list<IniSection>& _sections);
				IniFile(const std::initializer_list<IniSection*>& _sections);
				IniFile(const IniSection& _section);
				IniFile(IniSection* _section);
				IniFile(IniSection* _begin, IniSection* _end);
				~IniFile();

				IniSection section(const std::string& _name) const;
				IniSection* section(const std::string& _name);

				void section(IniSection* _section);
				void section(const IniSection& _section);
				void section(const std::initializer_list<IniSection>& _sections);
				void section(const std::initializer_list<IniSection*>& _sections);
				void section(IniSection* _begin, IniSection* _end);

				std::vector<IniSection*> sections() const;

				void remove_section(const std::string& _section_name);
				void clear();
			private:
				typedef std::vector<IniSection*> section_cointainer;

				section_cointainer sections_;

				section_cointainer::iterator find(const std::string& _section_name);
			};
		}
	}
}

