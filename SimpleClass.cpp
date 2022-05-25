#include <iostream>
#include <cstring>

using namespace std;

/*
	1. Возможность создания от класса std::string

	2. Операторы к реализации: == (оператор прямого сравнивания. Проверяет по данным, а не по существу. - что одна хранимая строчка внутри - одна и таже.),
	+= (+ и = напрямую не связаны и их поведение нужно вписывать вручную),
	! (должен принять строку и сказать что она не 1-ца. Мы знаем что срока пустая, но данные могут быть заполнены)

	3. Доступ к отдельным символам строки (перегрузка [], () )
		std::string str{"qwerty"};
		str[2]; // [] - прямой доступ. 
		str.at(2); // - прямой доступ, контролирует границы типа. Исключения генерируются
	оба метода принимают целое число, в каком месте нужно достучаться до данных.

	4. Предоставлять доступ к сырым данным
*/

	

class String {
public:

	// Задача 1
	String (std::string str1) {
		// узнать сколько символов в str

		capacity = str1.size ();
		size = std::size (str1);

		// выделить под них память
		data = new char[size] {};

		// скопировать данные из str
		::memcpy (data, &(str1[0]), size);
		
		// не забыть про остальные поля

	}

	// Задача 2
	bool operator ==(const String && other) {
		if (this->size != other.size) return false;
		for (int i = 0; i < this->size; i++)
		{
			if (this->data[i] != other.data[i]) return false;
		}
		return true;
	};

	friend bool operator +=(String a, String b) {
		//if (capacity >= ::strlen(str)) {
		//	for (int i = 0; i < size; i++) {
		//		data[i] = '\0';
		//	}
		//}
		//else
		//{
		//	if (data) {
		//		delete[] data;
		//	}
		//	data = new char[::strlen (str) + 1];
		//	capacity = ::strlen (str) + 1;
		//}
		//size = ::strlen (str);
		//::memcpy (data, str, size);
		//// процесс копирования
		//return *this;

	};

	friend bool operator !=(String a, String b) {
		
	};
	//friend bool operator !(String a); - описание, как привести к логике.

	// Задача 3

	//friend operator (bool) (String str); - описание, как привести к логике.

	char &operator[](int i) {

	};

	const char & operator[](int i) const {
	};
	

	String ()
		// Делигация. Быстрее, чем data = nullptr, size = 0, capacity = 0. Используется, когда нужно большие типы данных.
		:data (nullptr),
		size(0),
		capacity()
	{
		/*data = nullptr;
		size = 0;
		capacity = 0;*/
		cout << this << " Base object created\n"; // this - вывод адреса объекта
	}
	//explicit - нельзя вызвать 2 конструктора подряд. 

	// сначала - вызвать конструктор по умолчанию. Затем конструктор Base(int i). 
	explicit String(int length): String() {
		capacity = length;
		data = new char[length] {}; // если не писать {} - там будет мусор. А с ними - нули.
		//size = 0;
	}
	String (const char *str) {
		size = ::strlen (str)+1; // +1 потому-что последний символ не считается (\n)
		capacity = size;
		data = new char[size] {};
		::memcpy(data, str, size);
	}


	// Конструктор копирования.
	String (const String &other) {
		size = other.size;
		capacity = other.capacity;
		data = new char[other.size] {};
		::memcpy (data, other.data, size);
		cout << this << " Base object created by copy\n"; 
	}
	
	String (String && other):String() {
		std::swap (data, other.data);
		size = other.size;
		other.size = 0;
		std::swap (capacity, other.capacity);
	}

	~String () {
		if (data) {
			delete[] data; // Облегчение работы. При анализе кода. Правило приведения к bool
		}
		cout << this << " Base object destroyed\n"; // ~ - деструктор
	}

	void setString (const char *str) {
		(*this) = String (str);
	}

	// Чтобы работало присваивание a = b = static_cast<Base>(8); Иначе работать не будет.
	const String& operator = (const String &other) { 
		if (capacity >= other.size) {
			for (int i = 0; i < size; i++) {
				data[i] = '\0';
			}
		}
		else
		{
			if (data) {
				delete[] data;
			}
			data = new char[other.size + 1];
			capacity = other.size + 1;
		}
		size = other.size;
		::memcpy (data, other.data, size);
		// процесс копирования
		return *this;
	}

	friend String operator+(String a, String b);
private:
	// указатель на место, где хранится память
	char *data;
	// размер данных
	int size;
	// сколько памяти доступно
	int capacity;
};

String operator+(String a, String b) {
	String result (a.size + b.size);
	::memcpy (result.data, a.data, a.size);
	::memcpy (result.data + a.size, b.data, b.size); // арифметика указателей. Перемещение точки начала строки - куда мы будем переписывать дальше в оперативной памяти.
	result.size = a.size + b.size;
	return result;
}

// по параметру вызывается конструктор копирования
void F00 (String obj) {

}

int main () {
	String a; // вызов конструктора при создании объекта
	String b (5);
	// a = b = static_cast<String>(8);

	a = std::move(String("qwerty0") + String("asdfg"));
	String (); // создали анонимный объект
	String * point = new String (4); // auto point = new Base (4); - одно и тоже
	// F00(8) - так нельзя. Нам нужно вызвать явно этот конструтор 
	// F00 (Base (8));
	F00 (static_cast<String>(8)); // static cast - для отслеживания ошибок. Проведя дополнительные проверки. Чтобы программа не вылетела, а указала на ошибку.
	F00 (String ());   // F00 (b);
	delete point; // подчищение памяти после выделения памяти.
	double r = (1 / double (6));
	double e;
	e = r = 5.6; // По цепочку можем передавать данные. Если расширить цепочку a=b.
	return 0;
}