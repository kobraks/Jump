#pragma once
#include <vector>
#include <istream>
#include <ostream>
#include <regex>
#include <string>
#include<memory>

#include "Variable.hpp"

namespace ini
{
	/*
	W plik ini wygl�da nast�puj�co

	[nazwa sekcji]
	; komenta�e do sekcji
	zmienna = wartosc
	zmienna = wartoasc

	[nazwa sekcji 2]

	je�eli w pliku ini znajd� si� dwie takie same sekcjie to ta druga zast�puje pierwsz�
	wszystkie napisy po znaku ; - s� uwa�ane za komenta�.
	*/

	class Variable;

	class Section
	{
	public:
		Section();
		Section(std::wstring name, std::wstring valueName, std::wstring value);
		virtual ~Section();

		void setName(std::wstring name);										  							//Ustawia nazw� sekcji

		std::wstring getName();																					//Pobiera nazw� sekcji
		std::wstring getValue(std::wstring name);														//Pobie� warto�� z zmiennej

		void setValue(std::wstring& name, std::wstring& value);									//Ustawia warto�� zmiennej
		void addValue(std::wstring& name, std::wstring& value);									//Dodaj now� zmienn�
		void addCommentToValue(std::wstring name, std::wstring comment);				//Dodaje komentarz do zmiennej
		void addComment(std::wstring comment);														//Dodaje komentarz do sekcji
		void deleteComment(int line);																			//Usuwa okre�lon� linie komentarza sekcji
		void deleteValueComment(std::wstring variableName, int line);							//Usuwa okre�lon� linie komentarza zmiennej
		void deleteAllComments();																				//Usuwa wszystkie komentarze sekcji
		void deleteAllVariableComments(std::wstring varableName);							//Usuwa wszystkie komentarze zmiennej

		bool existValue(std::wstring valueName);															//Sprawdza czy istnieje podana nazwa zmiennej
		static int getNumberOfSectionsInFile(std::wstring name);
		static bool isSectionName(std::wstring line);
	private:
		std::wstring name;																							 // nazwa sekcji
		std::vector <std::shared_ptr<Variable>> variables;										 // poszczegulne zmienne w sekcji 
		std::vector <std::shared_ptr<std::wstring>> comments;								 // komentarze do sekcji

		std::shared_ptr<Variable> findVariable(std::wstring varableName);
	public:
		friend std::wistream& operator>> (std::wistream& in, Section& section)
		{
			std::wstring buff;							// Buffor  w kt�rym jest przechowywana aktualnie czytana linia tekstu
			bool find = false;							// Przechowuje informacje czy sekcja zosta�a ju� znaleziona
			std::wstring name = L"";				// Tymczasowe przechowanie nazwy sekcji
			int pos = in.tellg();						//	Pozycja czytania pliku

			while (std::getline(in, buff))
			{
				//std::wsmatch wynik;
				if (!buff.empty())
					if (buff.at(0) == L';' && find)																								//je�eli linia to komentarz
						if (section.variables.empty())
							section.comments.push_back(std::shared_ptr<std::wstring>(new std::wstring(buff)));	//je�eli niema jeszcze zmiennych to jest to komentarz sekcji
						else section.variables[section.variables.size() - 1]->addComment(buff);						//Je�eli s� ju� zmienne to dodaj do nich komentarz
					else
					{
						if (Section::isSectionName(buff))																		//Je�eli linia jest nazw� sekcji
						{
							if (!find)
							{
								pos = in.tellg();

								//zczytuje nazw� sekcji
								for (int i = 1; i < buff.length(); i++)
								{
									if (buff.at(i) == L']') break;
									else name += buff.at(i);
								}

								section.name = name;
								find = true;
							}
							else
							{
								in.seekg(pos);
								break;
							}
						}
						else if (find)
						{
							//Tworzy now� zmienn�

							pos = in.tellg();
							Variable var(buff);
							section.variables.push_back(std::shared_ptr<Variable>(new Variable(var)));
						}
					}
			}

			return in;
		}

		friend std::wostream& operator<< (std::wostream& out, const Section& sec)
		{
			if (Section::isSectionName(sec.name)) out << sec.name << std::endl;
			else out << L"[" + sec.name + L"]" << std::endl;

			for (auto element : sec.comments)
			{
				if (element->at(0) == L';') out << *element << std::endl;
				else out << L';' + *element << std::endl;
			}

			for (auto element : sec.variables)
			{
				out << *element;
			}

			return out;
		}
	};
}
