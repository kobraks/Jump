#pragma once

#include <string>

namespace mapf
{
	namespace priv
	{
		class Token
		{
		public:
			Token(std::wstring value, wchar_t op);

			std::wstring value;
			char op;
		};
	}
}
