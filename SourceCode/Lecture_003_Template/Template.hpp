#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <stdexcept>

class Complex {
public:
	// default constructor
	Complex() :real_{ 0.0 }, img_{ 0.0 } {}
	// overloading constructor
	Complex(double real, double img) : real_{ real }, img_{ img } {}

	double real_;
	double img_;
};

//! friend function for output members to out stream
std::ostream& operator<<(std::ostream& os, const Complex& u);

/*!
	template function for output value to ostream
	\param os out stream
	\param value template value
	\return out stream
*/
template<typename T>
std::ostream& PrintValue(std::ostream& os, const T& value)
{
	std::ostringstream oss;
	std::string strMessage;
	oss << "Template Function:" << __FUNCTION__ << "(" << typeid(value).name() << "):";

	try {
		os << oss.str() << value << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << oss.str() << error.what() << std::endl;
		throw error;
	}
	catch (...) {
		std::cerr << oss.str() << "caught unknow exception." << std::endl;
		throw "unknow exception";
	}
	return os;
}

/*!
	specialized template function for output int to ostream
	Print value to ostream
	\param os out stream
	\param value integer value
	\return out stream
*/
template<>
std::ostream& PrintValue(std::ostream& os, const int& value)
{
	std::ostringstream oss;
	std::string strMessage;
	oss << "Specialized template function for Integer:" << __FUNCTION__ << "(" << typeid(value).name() << "):";

	try {
		os << oss.str() << value << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << oss.str() << error.what() << std::endl;
		throw error;
	}
	catch (...) {
		std::cerr << oss.str() << "caught unknow exception." << std::endl;
		throw "unknow exception";
	}
	return os;
}

/*!
	specialized template function for output string to ostream
	Print value to ostream
	\param os out stream
	\param value string value
	\return out stream
*/
template<>
std::ostream& PrintValue(std::ostream& os, const std::string& value)
{
	std::ostringstream oss;
	std::string strMessage;
	oss << "Specialized template function for string:" << __FUNCTION__ << "(" << typeid(value).name() << "):";

	try {
		os << oss.str() << value << std::endl;
	}
	catch (std::exception& error) {
		std::cerr << oss.str() << error.what() << std::endl;
		throw error;
	}
	catch (...) {
		std::cerr << oss.str() << "caught unknow exception." << std::endl;
		throw "unknow exception";
	}
	return os;
}
