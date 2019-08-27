#pragma once

#include <memory>
#include <algorithm>
#include <initializer_list>

template<typename T>
class Array {
public:
    using size_type = size_t;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    using reference = T&;
    using const_reference = const T&;

    //! constructor
    Array() {
        create();
    }
    //! destructor
    virtual ~Array() {
        destroy();
    }
    //! constructor using size
    explicit Array(size_type sz, const_reference val = T()) {
        create(sz, val);
    }
    //! constructor using initializer_list
    Array(std::initializer_list<value_type> l) {
        create(l.begin(), l.end());
    }
    //! copy constructor
    Array(const Array& arr) {
        create(arr.begin(), arr.end());
    }
    //! assignment operation for references
    Array& operator=(const Array& arr) {
        Array temp(arr);
        swaper(temp);
        return *this;
    }
    //! move constructor
    Array(Array&& arr) noexcept : sz_(0), data_(nullptr) {
        swaper(arr);
    }
    //! move assignment
    Array& operator=(Array&& arr) {
        if (this != &arr) {
            if (data_)
                destroy();
            swaper(arr);
        }
        return *this;
    }
    //! if sz_ is 0 then to be return true otherwise false;
    bool empty() const { return sz_ ? true : false; }
    //! get size
    size_type size() const { return sz_; }
    //! clear all elements
    void clear() { destroy(); }
    //! begin
    iterator begin() { return data_; }
    //! end
    iterator end() { return data_+sz_; }
    //! const begin
    const_iterator begin() const { return data_; }
    //! const end
    const_iterator end() const { return data_+sz_; }
    //! random accesseble operator
    reference operator[](size_type i) { return data_[i]; }
    //! const random accesseble operator
    const_reference operator[](size_type i) const { return data_[i]; }

protected:

private:
    //! empty constructor helper
    void create(size_type sz = 0) {
        sz_ = sz;
        if (sz_) {
            data_ = new value_type[sz_];
        }
        else {
            data_ = nullptr;
        }
    }
    //! initialized constructor helper by size and value
    void create(size_type sz, const_reference val) {
        create(sz);
        std::uninitialized_fill_n(data_, sz_, val);
    }
    //! initialized constructor helper by iterators
    void create(const_iterator b, const_iterator e) {
        create(e-b);
        std::uninitialized_copy(b, e, data_);
    }
    // destructor helper
    void destroy() {
        sz_ = 0;
        if (data_) {
            delete [] data_;
        }
    }
    // swap helper
    void swaper(Array& arr) noexcept {
        std::swap(sz_, arr.sz_);
        std::swap(data_, arr.data_);
    }

    size_type sz_;      ///< data size
    iterator data_;     ///< data pointer
};
