#pragma once

#include <algorithm>
#include <initializer_list>
#include <cstddef>
#include <memory>

template <class T> class Vec {
public:
	using iterator = T *;
	using const_iterator = const T*;
	using size_type= size_t;
	using value_type = T;
	using reference = T & ;
	using const_reference = const T&;

	// constructors
	Vec() { create(); }
	explicit Vec(size_type n, const T& t = T()) { create(n, t); }
	Vec(const std::initializer_list<T> l) { create(l.begin(), l.end()); }
	Vec(const_iterator b, const_iterator e) { create(b, e); }
	Vec(const Vec& v) { create(v.begin(), v.end()); }
	Vec(Vec&& v) : data_{ v.data_ }, avail_{ v.avail_ }, limit_{ v.limit_ }
	{
		alloc_ = std::move(v.alloc_);
		v.data_ = v.avail_ = v.limit_ = 0;
	}

	Vec& operator=(const Vec&);
	Vec& operator=(Vec&&);

	virtual ~Vec() { uncreate(); }

	T& operator[](size_type i) { return data_[i]; }
	const T& operator[](size_type i) const { return data_[i]; }

	void push_back(const T& t) {
		if (avail_ == limit_)
			grow();
		unchecked_append(t);
	}
	//! get size
	size_type size() const noexcept { return avail_ - data_; }
	//! get capacity
	size_type capacity() const noexcept { return limit_ - data_; }

	//! front iterator
	iterator begin() noexcept { return data_; }
	const_iterator begin() const noexcept { return data_; }
	//! back iterator
	iterator end() noexcept { return avail_; }
	const_iterator end() const noexcept { return avail_; }
	
	//! clear elements
	void clear() { uncreate(); }
	//! is empty?
	bool empty() const noexcept { return data_ == avail_; }

private:
	iterator data_;  // first element in the `Vec'
	iterator avail_; // (one past) the last element in the `Vec'
	iterator limit_; // (one past) the allocated memory

	// facilities for memory alloc_ation
	std::allocator<T> alloc_;    // object to handle memory alloc_ation

	// allocate and initialize the underlying array
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	// destroy the elements in the array and free the memory
	void uncreate();

	// support functions for `push_back'
	void grow();
	void unchecked_append(const T&);
};

template <class T> void Vec<T>::create()
{
	data_ = avail_ = limit_ = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
	data_ = alloc_.allocate(n);
	limit_ = avail_ = data_ + n;
	std::uninitialized_fill(data_, limit_, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
	data_ = alloc_.allocate(j - i);
	limit_ = avail_ = std::uninitialized_copy(i, j, data_);
}

template <class T> void Vec<T>::uncreate()
{
	if (data_) {
		// destroy (in reverse order) the elements that were constructed
		iterator it = avail_;
		while (it != data_)
			alloc_.destroy(--it);

		// return all the space that was allocated
		alloc_.deallocate(data_, limit_ - data_);
	}
	// reset pointers to indicate that the `Vec' is empty again
	data_ = limit_ = avail_ = 0;

}

template <class T> void Vec<T>::grow()
{
	// when growing, allocate twice as much space as currently in use
	size_type new_size = std::max(2 * (limit_ - data_), ptrdiff_t(1));

	// allocate new space and copy existing elements to the new space
	iterator new_data_ = alloc_.allocate(new_size);
	iterator new_avail_ = std::uninitialized_copy(data_, avail_, new_data_);

	// return the old space
	uncreate();

	// reset pointers to point to the newly allocated space
	data_ = new_data_;
	avail_ = new_avail_;
	limit_ = data_ + new_size;
}

// assumes `avail_' points at allocated, but uninitialized space
template <class T> void Vec<T>::unchecked_append(const T& val)
{
	alloc_.construct(avail_++, val);
}

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
	// check for self-assignment
	if (&rhs != this) {

		// free the array in the left-hand side
		uncreate();

		// copy elements from the right-hand to the left-hand side
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

template <class T>
Vec<T>& Vec<T>::operator=(Vec&& rhs)
{
	data_ = rhs.data_;
	avail_ = rhs.avail_;
	limit_ = rhs.limit_;

	alloc_ = std::move(rhs.alloc_);
	rhs.data_ = rhs.avail_ = rhs.limit_ = 0;

	return *this;
}
