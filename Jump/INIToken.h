#pragma once
#include <string>

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniToken
			{
			public:
				IniToken(const char& _type, const std::string& _value) : type(_type), value(_value)
				{}

				IniToken() : type(0)
				{}

				char type;
				std::string value;
			};
		}
	}
}