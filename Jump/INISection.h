#pragma once

#include <vector>
#include <string>
#include <initializer_list>


#include "IniVariable.h"

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniSection
			{
			public:
				IniSection(const std::string& _name);
				IniSection(const std::string& _name, const std::initializer_list<IniVariable>& _variables);
				IniSection(const std::string& _name, const std::initializer_list<IniVariable*>& _variables);
				IniSection(const std::string& _name, const IniVariable _variable);
				IniSection(const std::string& _name, IniVariable* _variable);
				IniSection(const std::string& _name, IniVariable* _begin, IniVariable* _end);
				IniSection(const IniSection& _section);
				~IniSection();

				void name(const std::string& _name);
				std::string name() const;

				IniVariable variable(const std::string& _var_name) const;
				IniVariable* variable(const std::string& _variable);

				void variable(IniVariable* _variable);
				void variable(const IniVariable& _variable);
				void variable(const std::initializer_list<IniVariable>& _variables);
				void variable(const std::initializer_list<IniVariable*>& _variables);
				void variable(IniVariable* _begin, IniVariable* _end);

				std::vector<IniVariable*> variables() const;

				void remove_variable(const std::string& _variable_name);
				void clear();
			private:
				typedef std::vector<IniVariable*> variable_cointainer;

				std::string name_;
				variable_cointainer variables_;

				variable_cointainer::iterator find(const std::string& _var_name);
			};
		}
	}
}

