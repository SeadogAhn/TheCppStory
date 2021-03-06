#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <typeinfo>
#include <iomanip>
#include <stdexcept>

using namespace std;

void PrintSeparateLine(const string& str)
{
	try {
		cout << string(80, '-') << endl;
		cout << str << endl;
		cout << string(80, '-') << endl;
	}
	catch (exception& error) {
		cerr << __FUNCTION__ << '(' << str << ')' << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __FUNCTION__ << '(' << str << ')' << ": Unknown error caught." << endl;
	}
}

template< typename T >
void PrintValuesUsingRangeBasedLoop(const T& vals)
{
	string strTypeName = typeid(vals).name();

	try {
		cout << __FUNCTION__ << '(' << strTypeName << ')' << endl;
		cout << "Elements:";
		for (const auto& i : vals) {
			cout << i << ", ";
		}
		cout << endl;
	}
	catch (exception& error) {
		cerr << __FUNCTION__ << '(' << strTypeName << ')' << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __FUNCTION__ << '(' << strTypeName << ')' << ": Unknown error caught." << endl;
	}
}

template< typename T >
void PrintValuesForRandomAccessibleContainer(const T& vals, size_t nSize)
{
	string strTypeName = typeid(vals).name();
	try {
		cout << __FUNCTION__ << '(' << strTypeName << ')' << endl;
		cout << "Elements:";
		for (size_t i = 0; i != nSize; i++) {
			cout << vals[i] << ", ";
		}
		cout << endl;
	}
	catch (exception& error) {
		cerr << __FUNCTION__ << '(' << strTypeName << ')' << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __FUNCTION__ << '(' << strTypeName << ')' << ": Unknown error caught." << endl;
	}
}

template< typename T >
void PrintValuesForGenericContainer(const T& vals)
{
	typedef typename T::const_iterator const_iterator;
	string strTypeName = typeid(vals).name();
	try {
		cout << __FUNCTION__ << '(' << strTypeName << ')' << endl;
		cout << "Elements:";
		for (const_iterator citor = vals.begin(); citor != vals.end(); ++citor) {
			cout << *citor << ", ";
		}
		cout << endl;
	}
	catch (exception& error) {
		cerr << __FUNCTION__ << '(' << strTypeName << ')' << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __FUNCTION__ << '(' << strTypeName << ')' << ": Unknown error caught." << endl;
	}
}

int main(int argc, char** argv)
{
	try {
		string strMessage = "Hello world!";

		int arrNumber[]{ 0,1,2,3,4,5,6,7,8,9 };
		size_t nArrSize = sizeof(arrNumber) / sizeof(*arrNumber);

		vector<int> vecInt{ 0,1,2,3,4,5,6,7,8,9 };
		list<int> listInt{ 0,1,2,3,4,5,6,7,8,9 };

		PrintSeparateLine("range-based for loop");
		PrintValuesUsingRangeBasedLoop(strMessage);
		PrintValuesUsingRangeBasedLoop(arrNumber);
		PrintValuesUsingRangeBasedLoop(vecInt);
		PrintValuesUsingRangeBasedLoop(listInt);

		PrintSeparateLine("for loop");
		PrintValuesForRandomAccessibleContainer(strMessage, strMessage.size());
		PrintValuesForRandomAccessibleContainer(arrNumber, nArrSize);
		PrintValuesForRandomAccessibleContainer(vecInt, vecInt.size());

		PrintSeparateLine("for loop for generic container only");
		PrintValuesForGenericContainer(vecInt);
		PrintValuesForGenericContainer(listInt);

		PrintSeparateLine("example of for loop");
		for (auto& i : vecInt) {
			i = static_cast<int>(pow(i, 3));
		}
		PrintValuesUsingRangeBasedLoop(vecInt);

		int sum = 0;
		for (int i = 1, j = 1; i <= 10; sum += i + j, i++, j++);

		cout << "sum:" << sum << endl;

	}
	catch (exception& error) {
		cerr << __FUNCTION__ << "():" << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __FUNCTION__ << "():Unknown error caught." << endl;
	}
}
