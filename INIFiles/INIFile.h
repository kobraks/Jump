#pragma once

#include <string>
#include <vector>
#include <initializer_list>

#include "Exports.hpp"
#include "Section.h"

namespace ini
{
	class INIFILES INIFile
	{
	public:
		INIFile();
		INIFile(const std::initializer_list<Section>& _sections);
		INIFile(const std::initializer_list<Section*>& _sections);
		INIFile(const Section& _section);
		INIFile(Section* _section);
		INIFile(Section* _begin, Section* _end);
		~INIFile();

		Section section(const std::string& _name) const;
		Section* section(const std::string& _name);

		void section(Section* _section);
		void section(const Section& _section);
		void section(const std::initializer_list<Section>& _sections);
		void section(const std::initializer_list<Section*>& _sections);
		void section(Section* _begin, Section* _end);

		std::vector<Section*> sections() const;

		void remove_section(const std::string& _section_name);
		void clear();
	private:
		typedef std::vector<Section*> section_cointainer;

		section_cointainer sections_;

		section_cointainer::iterator find(const std::string& _section_name);
	};
}

