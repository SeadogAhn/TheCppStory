#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <complex>
#include <typeinfo>
#include <algorithm>

using namespace std;

int main()
{
	// boolean
	bool Boolean = true;
	// char
	char Character = 'c';
	// short
	short Short(2);
	// int
	int Integer(4);
	// long
	long Long(4);
    // double
	float Float{ 2.5 };
	// double
	double Double{ 3.5 };
	// complex
	complex<double> Complex{ 5.3, 7.2 };
	// string
	string String("String");
	// reference of string
	string& ReferenceOfString = String;
	// array of int
	int Array[5] = { 0, };
	// pointer to array
	int* Pointer = Array;
	// array of pointer
	int* PointerToArray[5] = { 0, };
	// array pointer
	int(*ArrayPointer)[5] = &Array;

	// vector container
	vector<int> vecInteger = { 0, 1, 2, 3, 4, 5 };
	// map container
	map<int, vector<int> > mapIntVector;
	mapIntVector.insert(make_pair(1, vecInteger));

	cout << typeid(vecInteger).name() << endl;
	for (auto& Val : vecInteger) {
		cout << Val << ' ';
	}
	cout << endl;

	cout << typeid(mapIntVector).name() << endl;
	for (const auto& KeyVal : mapIntVector) {
		cout << KeyVal.first << endl;
		cout << typeid(KeyVal.second).name() << endl;
		for (const auto& Val : KeyVal.second) {
			cout << Val << ' ';
		}
		cout << endl;
	}
}
