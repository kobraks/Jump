#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <memory>

namespace ini
{
	class Variable
	{
	public:
		Variable();																					//konstruktor domy�lny
		Variable(std::wstring name, std::wstring value);						//Konstruktor je�eli u�ywany aby stworzy� zmienn� o kore�lonej nazwie i warto�ci
		Variable(std::wstring line);														//Konstruktor tworz�cy zmienn� z lini
		virtual ~Variable();																	//Destruktor

		void addComment(std::wstring comment);								//Dodaje komentarz do zmiennej
		void deleteComment(int line);													//Usowa komentarz do zmiennej
		void deleteAllComments();														//Usuwa wszystkie komentarze
		void setValue(std::wstring value);												//Ustawia warto��
		void setName(std::wstring name);											//Ustawia nazw�

		std::wstring getName();															//Odczytuje nazw� zmiennej
		std::wstring getValue();															//Odczytuje warto�� zmiennej
		std::wstring getComment(int line);											//Odczytuje komentarz w danej lini
		std::vector <std::wstring> getComments();							//Odczytuje wszystkie komentarze
		std::wstring getLine();																//Pobiera linie kt�r� trzeba zapisac do pliku
	private:
		std::wstring name;																	//Nazwa zmiennej
		std::wstring var;																		//Warto�� zmiennej
		std::vector <std::shared_ptr<std::wstring>> comments;		//Komentarze do zmiennej

	public:
		friend std::wostream& operator<< (std::wostream& out, Variable& var)
		{
			out << var.getLine() << std::endl;

			if (!var.comments.empty())
			{
				for (auto element : var.comments)
				{
					if (element->at(0) == L';') out << *element << std::endl;
					else out << L";" + *element << std::endl;
				}
			}

			return out;
		}
	};
}
