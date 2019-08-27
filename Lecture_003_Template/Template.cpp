// user headers
#include "Template.hpp"
// standard headers

using namespace std;

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
	os << '(' << c.real_ << ',' << c.img_ << ')';
	return os;
}

int main(int argc, char** argv)
{
	ostringstream oss;
	string strMessage;
	oss << __FUNCTION__ << "():";

	try {
		char c = 'a';
		int n = 100;
		double d = 2.34;
		Complex cplx{ 3.2, 4.3 };
		char szStr[] = "Character array";
		string str{ "string literal" };

		// using template function
		PrintValue(cout, c);
		PrintValue(cout, d);
		PrintValue(cout, cplx);
		PrintValue(cout, szStr);

		cout << endl;

		// using specialized template functions
		PrintValue(cout, n);
		PrintValue(cout, str);

	}
	catch (exception& error) {
		cerr << oss.str() << error.what() << endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		cerr << oss.str() << "caught exception unknown error." << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
