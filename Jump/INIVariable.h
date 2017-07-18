#pragma once
#include <string>



namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniVariable
			{
			public:
				IniVariable(const std::string& _name, const std::string& _value) : name(_name), value(_value)
				{}

				IniVariable() {}
				~IniVariable() {};

				std::string name;
				std::string value;
			};
		}
	}
}

