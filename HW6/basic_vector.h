#ifndef BASIC_VECTOR_H_DEFINED
#define BASIC_VECTOR_H_DEFINED
#include <string>
#include <iostream>
#include <cstddef>
#include <cmath>

// George Krier - 835973055

template <typename T>
class basic_vector {
    T* data_; // Pointer to data array
    size_t size_; // Size of the currently stored data
    size_t capacity_; // Capacity before reallocation occurs

public:
    basic_vector() : basic_vector(1) {}

    basic_vector(size_t capacity) {
        size_ = 0;
        capacity_ = capacity;
        data_ = new T[capacity_];
    }
    
    basic_vector(const basic_vector &rhs) {
        size_ = rhs.size();
        capacity_ = rhs.capacity();
        data_ = new T[capacity_];
        std::copy(rhs.data_, rhs.data_ + size_, data_);
    }
    
    basic_vector& operator=(const basic_vector &rhs) {
        size_ = rhs.size();
        capacity_ = rhs.capacity();
        data_ = new T[capacity_];
        std::copy(rhs.data_, rhs.data_ + size_, data_);
        return *this;
    }

    // Capacity Methods

    size_t size() const {
        return size_;
    }

    size_t max_size() const {
        return pow(2, 32 - sizeof(T)) - 1;
    }

    size_t capacity() const {
        return capacity_;
    }

    void resize(size_t n) {
        resize(n, T());
    }

    void resize(size_t n, const T &val) {
        if (size_ == n || (n < capacity_ && n > size_)) return; // If current size = n or (if n is less than capacity and greater than size) return without doing anything 
        T* new_data;

        if (n > capacity_) { // If n is greater than capacity, new capacity is n
            capacity_ = n;
        }
        new_data = new T[capacity_];

        std::fill(new_data, new_data + capacity_, val);

        if (n < size_) { // New size less than current size - Truncate
            size_ = n;
        }

        std::copy(data_, data_ + size_, new_data); // Truncate to new size and copy

        delete[] data_;
        data_ = new_data;
    }

    bool empty() {
        return size_ == 0;
    }

    void reserve(size_t n) {
        if (n > max_size()) {
            resize(max_size());
        } else if (n > capacity_) {
            resize(n);
        }
    }

    void shrink_to_fit() {
        if (size_ != capacity_) {
            T* arr = new T[size_];
            std::copy(data_, data_ + size_, arr);
            delete[] data_;
            data_ = arr;
        }
    }


    // Element Access
    T& operator[](size_t n) {
        return data_[n];
    }

    const T& operator[](size_t n) const {
        return data_[n];
    }

    T& at(size_t n) {
        if (n < 0 || n > size_) {
            throw std::range_error("Invalid index");
        }
        return data_[n];
    }

    T& front() {
        if (size_ == 0) {
            throw std::range_error("Cannot return front since basic_vector has no elements.");
        }
        return data_[0];
    }

    T& back() {
        if (size_ == 0) {
            throw std::range_error("Cannot return front since basic_vector has no elements.");
        }
        return data_[size_ - 1];
    }
    
    T* data() {
        return data_;
    }

    // Modifiers

    void push_back(const T& val) { // Puts the element val onto the end of the vector, reallocating as necessary.
        resize(capacity_ * 2);
        capacity_ *= 2;
        data_[size_++] = val;
    }
    
    void pop_back() { // removes the last element in the vector reducing size by one.
        data_[size_ - 1] = T();
        size_--;;
    }
    
    void swap(basic_vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void clear() {
        std::fill(data_, data_ + capacity_, T());
        size = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const basic_vector& obj) {
        os << "Size: " << obj.size() << "\n";
        if (obj.size() == 0) {
            os << "[ ]\n" << std::endl;
        } else {
            os << "[" << obj[0];
            for (size_t i=1; i < obj.size(); i++) {
                os << ", "<< obj[i];
            }
            os << "]" << std::endl;
        }
        return os;
    }

private:

};

#endif