#pragma once
#include <string>

#include "Exports.hpp"

namespace ini
{
	class Variable
	{
	public:
		Variable(const std::string& _name, const std::string& _value) : name(_name), value(_value)
		{}

		Variable() {}
		~Variable() {};

		std::string name;
		std::string value;
	};
}

