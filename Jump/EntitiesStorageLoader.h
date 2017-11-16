#pragma once
#include <string>
#include <vector>

namespace jump
{
	namespace entity
	{
		class EntitiesStorageLoader
		{
		public:
			explicit EntitiesStorageLoader(const std::string& file_name);
			~EntitiesStorageLoader();

			std::vector<std::string> get_entities_names() const;

		private:
			std::vector<std::string> names_;
		};
	}
}

