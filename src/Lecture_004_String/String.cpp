#include "String.hpp"

#include <cstring>
#include <algorithm>
#include <stdexcept>

String::String()
{
	create();
}

String::String(const value_type* str)
{
	create(str, std::strlen(str));
}

String::String(const String& str)
{
	std::cout << "copy constructor" << std::endl;
	create(str.begin(), str.end());
}

String::~String()
{
	uncreate();
}

String& String::operator=(const String& rhs)
{
	std::cout << "assign operator" << std::endl;
	// check for self-assignment
	if (&rhs != this) {
		// free the array in the left-hand side
		uncreate();
		// copy elements from the right-hand to the left-hand side
		create(rhs.begin(), rhs.end());
	}
	return *this;
}


String& String::operator+=(const String& cs)
{
	size_type szOld = size();
	size_type szNew = szOld + cs.size();

	iterator newData = alloc.allocate(szNew + 1);
	std::uninitialized_fill(newData, newData + szNew + 1, 0);
	std::uninitialized_copy(data, data + size(), newData);
	std::uninitialized_copy(cs.begin(), cs.end(), newData + szOld);

	uncreate();

	data = newData;
	avail = data + szNew;

	return *this;
}

void String::create()
{
	data = alloc.allocate(1);
	std::uninitialized_fill(data, data + 1, 0);
	avail = data;
}

void String::create(const value_type* str, size_type sz)
{
	data = alloc.allocate(sz + 1);
	std::uninitialized_fill(data, data + sz + 1, 0);
	avail = std::uninitialized_copy(str, str+sz, data);
}

void String::create(const_iterator i, const_iterator j)
{
	size_type sz = j - i;
	data = alloc.allocate(sz + 1);
	std::uninitialized_fill(data, data + sz + 1, 0);
	avail = std::uninitialized_copy(i, j, data);
}

void String::uncreate()
{
	if (data) {
		// destroy (in reverse order) the elements that were constructed
		iterator it = avail;
		while (it != data)
			alloc.destroy(--it);
		alloc.deallocate(data, avail - data + 1);
	}
	// reset pointers to indicate that the `String' is empty again
	data = avail = 0;
}

const char* String::c_str() const noexcept
{
	return data;
}

std::ostream& operator<< (std::ostream& os, const String& cs)
{
	os << cs.c_str();
	return os;
}

std::istream& operator>> (std::istream& is, String& cs)
{
	char str[2048];
	is >> str;
	cs = str;
	return is;
}

const String operator+(const String& cs1, const String& cs2)
{
	String temp(cs1);
	temp += cs2;
	return temp;
}
