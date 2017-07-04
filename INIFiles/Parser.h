#pragma once
#include <vector>

#include "Token.h"
#include "Section.h"

namespace ini
{
	namespace priv
	{
		class Parser
		{
		public:
			Parser(std::vector<Token*>& _tokens);

			std::vector<ini::Section*> parse();
		private:
			std::vector<Token*> tokens_;
		};
	}
}