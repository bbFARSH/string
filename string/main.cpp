#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
class String;
String operator+(const String& left, const String& right);

class String
{
	int size; 
	char* str; 
public:
	//	Constructor
	explicit String(int size = 80) :size(size), str(new char[size] {})
	{
		//this->size = size;
		//this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char* str) : String(strlen(str)+1) // Делегируем выделение памяти конструктору по умолчанию
	{
		//this->size = strlen(str) + 1;
		//this->str = new char[size] {};
		//for (int i = 0; i < size; i++)this->str[i] = str[i];
		strcpy(this->str, str);
		//strcpy - string copy
		//strcpy - (dst, src);
		//dst - destination, строка получатель
		//src - source, строка источник, строка, из которой копируется содержимое.
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other):String(other.str)
	{
		//this->size = other.size;
		//this->str = new char[size] {};
		//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	String(String&& other): size(other.size), str(other.str)
	{
		//shallow copy
		//move-конструктор должен работать так, как не должен работать конструктор копирования(диаметральная противоположность)
		//this->size = other.size;
		//this->str = other.str;
		cout << "MoveConstructor:\t\t" << this << endl;
		other.str = nullptr;
		other.size = 0;
	}
	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssigment:\t\t" << this << endl;
		return *this;
	}
	String& opearator(String&& other)
	{
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		other.size;
		return *this;
	}
	String operator+=(const String& other)
	{
		return *this = *this + other;
	}

	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}

	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	 char* get_str()
	{
		return str;
	}
	 const char &operator[](int i)const
	 {
		 return str[i];
	 }
	 char& operator[](int i)
	 {
		 return str[i];
	 }

};
String operator+(const String& left, const String& right)
{
	String buffer(left.get_size() + right.get_size() - 1);
	strcpy (buffer.get_str(), left.get_str());
	strcat(buffer.get_str(), right.get_str());
#ifdef fori
	for (int i = 0; i < left.get_size(); i++)
		buffer[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		buffer[i + left.get_size() - 1] = right[i];
#endif // fori
	//strcat - выполняет контатенацию строк
	//strcat(dst,src);
	//dst - строка получатель
	//src - строка источник
	// В dst будет объеденная строка
	return buffer;
}
ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

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