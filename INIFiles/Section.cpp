#include "Section.h"
#include <algorithm>
#include "INIFileBadAllocException.h"
#include "INIFileVariableDoesNotExistsException.h"
#include <exception>

ini::Section::Section(const std::string& _name) : name_(_name)
{}

ini::Section::Section(const std::string& _name, const std::initializer_list<Variable*>& _variables) : Section(_name)
{
	variable(_variables);
}

ini::Section::Section(const std::string& _name, const std::initializer_list<Variable>& _variables) : Section(_name)
{
	variable(_variables);
}

ini::Section::Section(const std::string& _name, const Variable _variable) : Section(_name)
{
	variable(_variable);
}

ini::Section::Section(const std::string& _name, Variable* _variable) : Section(_name)
{
	variable(_variable);
}

ini::Section::Section(const std::string& _name, Variable* _begin, Variable* _end) : Section(_name)
{
	variable(_begin, _end);
}

ini::Section::Section(const Section& _section)
{
	try
	{
		for (auto variable : _section.variables_)
			variables_.push_back(new Variable(*variable));

		name_ = _section.name();
	}
	catch(std::bad_alloc)
	{
		throw exception::INIFileBadAllocException();
	}
}

ini::Section::~Section()
{
	clear();
}

void ini::Section::clear()
{
	for (auto variable : variables_)
		delete variable;

	variables_.clear();
}

void ini::Section::name(const std::string& _name)
{
	if (_name != "" || !_name.empty())
		name_ = _name;
}

std::string ini::Section::name() const
{
	return name_;
}

ini::Variable ini::Section::variable(const std::string& _var_name) const
{
	auto result = std::find_if(variables_.begin(), variables_.end(), [_var_name](const Variable const* _variable) { return _var_name == _variable->name; });

	if (result != variables_.end())
		return **result;
	else
		throw exception::INIFileVariableDoesNotExistsException();
}

ini::Variable* ini::Section::variable(const std::string& _variable)
{
	auto result = find(_variable);

	if (result != variables_.end())
		return *result;
	else
		throw exception::INIFileVariableDoesNotExistsException();
}


void ini::Section::variable(Variable* _variable)
{
	if (_variable)
	{
		auto var = find(_variable->name);

		if (var != variables_.end())
		{
			size_t pos = std::distance(variables_.begin(), var);
			delete variables_[pos];
			variables_[pos] = _variable;
		}
		else
			variables_.push_back(_variable);
	}
}

void ini::Section::variable(const Variable& _variable)
{
	try
	{
		auto var = find(_variable.name);

		if (var != variables_.end())
		{
			size_t pos = std::distance(variables_.begin(), var);
			variables_[pos]->value = _variable.value;
		}
		else
			variables_.push_back(new Variable(_variable));
	}
	catch(std::bad_alloc)
	{
		throw exception::INIFileBadAllocException();
	}
}

std::vector<ini::Variable*> ini::Section::variables() const
{
	return variables_;
}

void ini::Section::variable(Variable* _begin, Variable* _end)
{
	for (auto i = _begin; i != _end; ++i)
		variable(*i);
}

void ini::Section::variable(const std::initializer_list<Variable>& _variables)
{
	for (auto variable : _variables)
		this->variable(variable);
}

void ini::Section::variable(const std::initializer_list<Variable*>& _variables)
{
	for (auto variable : _variables)
		this->variable(variable);
}

std::vector<ini::Variable*>::iterator ini::Section::find(const std::string& _var_name)
{
	return std::find_if(variables_.begin(), variables_.end(), [_var_name](const Variable const* _variable) { return _var_name == _variable->name; });
}

void ini::Section::remove_variable(const std::string& _variable_name)
{
	auto variable = find(_variable_name);

	if (variable == variables_.end())
		throw exception::INIFileVariableDoesNotExistsException();

	size_t pos = std::distance(variables_.begin(), variable);
	delete variables_[pos];
	variables_.erase(variables_.begin() + pos);
}
