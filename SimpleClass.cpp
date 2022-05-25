#include <iostream>
#include <cstring>

using namespace std;

/*
	1. ����������� �������� �� ������ std::string

	2. ��������� � ����������: == (�������� ������� �����������. ��������� �� ������, � �� �� ��������. - ��� ���� �������� ������� ������ - ���� � ����.),
	+= (+ � = �������� �� ������� � �� ��������� ����� ��������� �������),
	! (������ ������� ������ � ������� ��� ��� �� 1-��. �� ����� ��� ����� ������, �� ������ ����� ���� ���������)

	3. ������ � ��������� �������� ������ (���������� [], () )
		std::string str{"qwerty"};
		str[2]; // [] - ������ ������. 
		str.at(2); // - ������ ������, ������������ ������� ����. ���������� ������������
	��� ������ ��������� ����� �����, � ����� ����� ����� ����������� �� ������.

	4. ������������� ������ � ����� ������
*/

	

class String {
public:

	// ������ 1
	String (std::string str1) {
		// ������ ������� �������� � str

		capacity = str1.size ();
		size = std::size (str1);

		// �������� ��� ��� ������
		data = new char[size] {};

		// ����������� ������ �� str
		::memcpy (data, &(str1[0]), size);
		
		// �� ������ ��� ��������� ����

	}

	// ������ 2
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
		//// ������� �����������
		//return *this;

	};

	friend bool operator !=(String a, String b) {
		
	};
	//friend bool operator !(String a); - ��������, ��� �������� � ������.

	// ������ 3

	//friend operator (bool) (String str); - ��������, ��� �������� � ������.

	char &operator[](int i) {

	};

	const char & operator[](int i) const {
	};
	

	String ()
		// ���������. �������, ��� data = nullptr, size = 0, capacity = 0. ������������, ����� ����� ������� ���� ������.
		:data (nullptr),
		size(0),
		capacity()
	{
		/*data = nullptr;
		size = 0;
		capacity = 0;*/
		cout << this << " Base object created\n"; // this - ����� ������ �������
	}
	//explicit - ������ ������� 2 ������������ ������. 

	// ������� - ������� ����������� �� ���������. ����� ����������� Base(int i). 
	explicit String(int length): String() {
		capacity = length;
		data = new char[length] {}; // ���� �� ������ {} - ��� ����� �����. � � ���� - ����.
		//size = 0;
	}
	String (const char *str) {
		size = ::strlen (str)+1; // +1 ������-��� ��������� ������ �� ��������� (\n)
		capacity = size;
		data = new char[size] {};
		::memcpy(data, str, size);
	}


	// ����������� �����������.
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
			delete[] data; // ���������� ������. ��� ������� ����. ������� ���������� � bool
		}
		cout << this << " Base object destroyed\n"; // ~ - ����������
	}

	void setString (const char *str) {
		(*this) = String (str);
	}

	// ����� �������� ������������ a = b = static_cast<Base>(8); ����� �������� �� �����.
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
		// ������� �����������
		return *this;
	}

	friend String operator+(String a, String b);
private:
	// ��������� �� �����, ��� �������� ������
	char *data;
	// ������ ������
	int size;
	// ������� ������ ��������
	int capacity;
};

String operator+(String a, String b) {
	String result (a.size + b.size);
	::memcpy (result.data, a.data, a.size);
	::memcpy (result.data + a.size, b.data, b.size); // ���������� ����������. ����������� ����� ������ ������ - ���� �� ����� ������������ ������ � ����������� ������.
	result.size = a.size + b.size;
	return result;
}

// �� ��������� ���������� ����������� �����������
void F00 (String obj) {

}

int main () {
	String a; // ����� ������������ ��� �������� �������
	String b (5);
	// a = b = static_cast<String>(8);

	a = std::move(String("qwerty0") + String("asdfg"));
	String (); // ������� ��������� ������
	String * point = new String (4); // auto point = new Base (4); - ���� � ����
	// F00(8) - ��� ������. ��� ����� ������� ���� ���� ���������� 
	// F00 (Base (8));
	F00 (static_cast<String>(8)); // static cast - ��� ������������ ������. ������� �������������� ��������. ����� ��������� �� ��������, � ������� �� ������.
	F00 (String ());   // F00 (b);
	delete point; // ���������� ������ ����� ��������� ������.
	double r = (1 / double (6));
	double e;
	e = r = 5.6; // �� ������� ����� ���������� ������. ���� ��������� ������� a=b.
	return 0;
}