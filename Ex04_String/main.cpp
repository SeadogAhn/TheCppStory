#include "MyString.hpp"

using namespace std;

void func(CString str)
{
	cout << str << endl;
}

int main()
{
	// using default constructor
	CString str1;
	cout << str1 << 'A' << endl;
	cout << str1.size() << endl;
	cout << sizeof(str1) << endl;
	// using assign operator
	str1 = "Hello";
	// using overloded constructor
	CString str2 = "World!";
	// using overloded constructor after using operator+
	CString str3 = str1 + " " + str2;
	// usng overloded operator<<
	cout << str1 << ' ' << str1.size() << endl;
	cout << str2 << ' ' << str2.size() << endl;
	cout << str3 << ' ' << str3.size() << endl;
	cout << sizeof(str3) << endl;

	cout << "Type the string : ";
	// using overloaded opeartor>>
	cin >> str1;
	// using operator+=
	str2 += str1;
	
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	CString str = "0123456789";
	// using std::reverse algorithm with begin & end are iterator
	reverse(str.begin(), str.end());
	cout << str << endl;

	CString::iterator pos = find(str.begin(), str.end(), '7');
	cout << distance(str.begin(), pos) << endl;

	// using range based loop
	for (auto& c : str) {
		cout << c;
	}
	cout << endl;

	// using operator[]
	cout << str[2] << endl;

	str3 = " " + str2;

	cout << str3 << endl;

	func(str3);

	return EXIT_SUCCESS;
}
