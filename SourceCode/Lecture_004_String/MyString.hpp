#pragma once

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <memory>

class CString {
public:
	typedef char value_type;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef size_t size_type;
	// friend functions for in, out stream
	friend std::ostream& operator<< (std::ostream& os, const CString& cs);
	friend std::istream& operator>> (std::istream& is, CString& cs);
	//! default constructor
	CString();
	//! constructor overloading
	CString(const value_type* str);
	//! constructor overloading
	CString(const CString& str);
	//! destructor
	virtual ~CString();
	//! operator= overloading
	CString& operator=(const CString& str);
	//! operator+= overaloding
	CString& operator+=(const CString& cs);
	//! operator[]
	value_type& operator[](size_type i) { return data[i]; }
	//! operator[] const
	const value_type& operator[] (size_type i) const { return data[i]; }
	//! size
	size_type size() const noexcept { return avail - data; }
	//! c type string
	const char* c_str() const noexcept;
	//! begin
	iterator begin() noexcept { return data; }
	//! const begin
	const_iterator begin() const noexcept { return data; }
	//! end
	iterator end() noexcept { return avail; }
	//! const end
	const_iterator end() const noexcept { return avail; }
	//! clear data
	void clear() { uncreate(); }
	//! is empty
	bool empty() const noexcept { return data == avail; }
private:
	//! initial
	void create();
	//! create & allocate memory
	void create(const value_type* str, size_type sz);
	//! create string using const iterators
	void create(const_iterator i, const_iterator j);
	//! destroy memory
	void uncreate();

	//! facilities for memory allocation
	std::allocator<value_type> alloc;

	iterator data;  ///< first element in the `MyString'
	iterator avail;	///< (one past) the allocated memory
};

const CString operator+ (const CString& cs1, const CString& cs2);
