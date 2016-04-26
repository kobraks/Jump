#pragma once

#include <vector>
#include <map>
#include <string>

#include "Token.h"

namespace mapf
{
	namespace priv
	{
		class Parser
		{
		public:
			Parser(std::vector<Token*> tokens);
			~Parser();

			std::wstring parseValue();
			std::map<std::wstring, std::wstring> lunch();
		private:
			std::vector<Token*> tokens;
			std::map < std::wstring, std::wstring> map;
			int i;
		};
	}
}
