#pragma once
#include <string>

namespace ini
{
	namespace priv
	{
		class Token
		{
		public:
			Token(const char& _type, const std::string& _value) : type(_type), value(_value)
			{}

			Token() : type(0)
			{}

			char type;
			std::string value;
		};
	}
}