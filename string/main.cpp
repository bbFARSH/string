#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
class String;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Объявление класса - CLass Declaration////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String operator+(const String& left, const String& right);

class String
{
	int size; 
	char* str; 
public:
	//	Constructor
	explicit String(int size = 80);
	String(const char* str);
	String(const String& other);
	String(String&& other);
	~String();
	//			Operators:
	String& operator=(const String& other);
	String& opearator(String&& other);
	String operator+=(const String& other);
	void print()const;

	int get_size()const;
	const char* get_str()const;
	char* get_str();
	 const char& operator[](int i)const;
	 char& operator[](int i);

};
/////////////////// КОНЕЦ ОБЪЯВЛЕНИЯ КЛАССА //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////ОПРЕДЕЛЕНИЕ КЛАССА - CLASS DEFINITION       ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "DefaultConstructor:\t" << this << endl;
}
String::String(const char* str) : String(strlen(str) + 1) // Делегируем выделение памяти конструктору по умолчанию
{
	//this->size = strlen(str) + 1;
	//this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = str[i];
	cout << "Constructor:\t\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	//this->size = other.size;
	//this->str = new char[size] {};
	//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other) : size(other.size), str(other.str)
{
	//shallow copy
	//move-конструктор должен работать так, как не должен работать конструктор копирования(диаметральная противоположность)
	//this->size = other.size;
	//this->str = other.str;
	cout << "MoveConstructor:\t\t" << this << endl;
	other.str = nullptr;
	other.size = 0;
}
String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t\t" << this << endl;
}

//			Operators:
String& String::operator=(const String& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyAssigment:\t\t" << this << endl;
	return *this;
}
String& String::opearator(String&& other)
{
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;
	other.size;
	return *this;
}
String String::operator+=(const String& other)
{
	return *this = *this + other;
}

void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
const char& String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}
::String operator+(const String& left, const String& right)
{
	String buffer(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		buffer[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		buffer[i + left.get_size() - 1] = right[i];
	return buffer;
}
std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
/////////////////// КОНЕЦ ОПРЕДЕЛЕНИЯ КЛАСССА //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define CONSTRUCTOR_CHECK
//#define operator_plus_check
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTOR_CHECK
	String str;
	str.print();
	String str1 = "Hello";
	//str1.print();
	cout << str1 << endl;

	String str2 = str1;
	cout << str2 << endl;
	String str3;
	str3 = str2;
	cout << str3 << endl;
#endif // CONSTRUCTOR_CHECK

#ifdef DEBUG
	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;
#endif // DEBUG

#ifdef operators_plus_check
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + str2;
	cout << str3 << endl;
	str1 += str2;
	cout << str1 << endl;
#endif // operators_plus_check

	String str1(25);
	str1.print();          // Default constructor
	String str2 = "Hello"; // Single-argument constructor
	str2.print();
	String str3("World"); // Single-argument constructor
	cout << str3 << endl;
	String str4(); // ЗДЕСЬ НЕ СОЗДАЕТСЯ ОБЪЕКТ, А Объявляем ф-ия str4, 
	               //которая ничего не принимает и возвращает объект класса string
	String str5{}; // ЯВНЫЙ ВЫЗОВ КОНСТРУКТОРА ПО УМОЛЧАНИЮ
	cout << str5 << endl;
	String str6{ "Параметры в конструктор можно передавать в фигурных скобках" };
	cout << str6 << endl;
	String str7 = str6;
	cout << str7 << endl;
	cout << str2 + " " + str3 << endl;
}