#pragma once
#include <string>
#include <RapidXml\rapidxml.hpp>
#include <SFML\Graphics.hpp>

namespace jump
{
	namespace system
	{
		namespace xml
		{
			inline char* stringToChar(std::string & s);
			char* fileToChar(std::string& fileName);
			std::string getAttributeValue(rapidxml::xml_node <>* wezel, std::string atributeName);
			sf::IntRect getRectFromXMLFile(std::string fileName, std::string attributeName, std::string attribute);
		}
	}
}