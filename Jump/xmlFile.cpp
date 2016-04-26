#include "xmlFile.h"

#include <boost\algorithm\string.hpp>
#include <fstream>

#include "Log.h"

using namespace jump;
using namespace system;

inline char* xml::stringToChar(std::string & s)
{
	auto length = s.length();

	char* out = new char[length + 1];

	std::copy(s.c_str(), (s.c_str() + length - 1), out);

	return out;
}

char* xml::fileToChar(std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.good())
	{
		std::filebuf* fbuf = file.rdbuf();

		auto fileLength = fbuf->pubseekoff(0, std::ios::end, std::ios::in);
		file.seekg(0);

		char* out = new char[fileLength];

		file.read(out, fileLength);

		return out;
	}

	FILE_LOG(logERROR) << "Cannot open a " << fileName;
	return NULL;
}

std::string xml::getAttributeValue(rapidxml::xml_node <>* wezel, std::string atributeName)
{
	for (auto atribe = wezel->first_attribute(); atribe; atribe = atribe->next_attribute())
	{
		std::string name = atribe->name();

		if (boost::to_upper_copy(name) == boost::to_upper_copy(atributeName))
		{
			return atribe->value();
		}
	}
}

sf::IntRect xml::getRectFromXMLFile(std::string fileName, std::string attributeName, std::string attribute)
{
	sf::IntRect rect;

	auto pos = fileName.find(".");
	if (pos != std::string::npos) fileName.erase(pos);
	fileName += ".xml";

	rapidxml::xml_document <> doc;

	std::auto_ptr<char> file(fileToChar(fileName));

	try
	{
		doc.parse < 0 >(file.get());
	}
	catch (rapidxml::parse_error p)
	{
		FILE_LOG(logINFO) << p.what();
	}

	//std::cout << doc;

	rapidxml::xml_node <> * node = doc.first_node();

	for (auto gal = node->first_node(); gal; gal = gal->next_sibling())
	{
		if (boost::to_lower_copy(getAttributeValue(gal, attributeName)) == boost::to_lower_copy(attribute))
		{
			rect.left = std::stoi(getAttributeValue(gal, "x"));
			rect.top = std::stoi(getAttributeValue(gal, "y"));
			rect.height = std::stoi(getAttributeValue(gal, "height"));
			rect.width = std::stoi(getAttributeValue(gal, "width"));

			break;
		}
	}

	doc.clear();

	return rect;
}