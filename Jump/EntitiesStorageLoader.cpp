#include "EntitiesStorageLoader.h"
#include <fstream>

#include "UnableToOpenFileException.h"

jump::entity::EntitiesStorageLoader::EntitiesStorageLoader(const std::string& file_name)
{
	std::ifstream file(file_name, std::ios::in);

	if (!file.good())
		throw system::exception::UnableToOpenFileException(file_name);

	std::string line;
	while (std::getline(file, line))
	{
		names_.push_back(line);
	}

	file.close();
}

jump::entity::EntitiesStorageLoader::~EntitiesStorageLoader()
{
	names_.clear();
}

std::vector<std::string> jump::entity::EntitiesStorageLoader::get_entities_names() const
{
	return names_;
}
