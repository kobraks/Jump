#pragma once

#include <vector>
#include <string>
#include <initializer_list>

#include "Exports.hpp"
#include "Variable.h"

namespace ini
{
	class INIFILES Section
	{
	public:
		Section(const std::string& _name);
		Section(const std::string& _name, const std::initializer_list<Variable>& _variables);
		Section(const std::string& _name, const std::initializer_list<Variable*>& _variables);
		Section(const std::string& _name, const Variable _variable);
		Section(const std::string& _name, Variable* _variable);
		Section(const std::string& _name, Variable* _begin, Variable* _end);
		Section(const Section& _section);
		~Section();

		void name(const std::string& _name);
		std::string name() const;

		Variable variable(const std::string& _var_name) const;
		Variable* variable(const std::string& _variable);

		void variable(Variable* _variable);
		void variable(const Variable& _variable);
		void variable(const std::initializer_list<Variable>& _variables);
		void variable(const std::initializer_list<Variable*>& _variables);
		void variable(Variable* _begin, Variable* _end);

		std::vector<Variable*> variables() const;

		void remove_variable(const std::string& _variable_name);
		void clear();
	private:
		typedef std::vector<Variable*> variable_cointainer;

		std::string name_;
		variable_cointainer variables_;

		variable_cointainer::iterator find(const std::string& _var_name);
	};
}

