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
    /** basic_vector()
    * @param None
    * @return Calls the basic_vector(size_t) constructor with a default capacity of 1
    */
    basic_vector() : basic_vector(1) {}
    
    /** basic_vector(size_t)
    * @param capacity The initial capacity to set the array to.
    * @return Sets array capacity to capacity provided and defaults size to 0, also initializes the data array.
    */
    basic_vector(size_t capacity) {
        size_ = 0;
        capacity_ = capacity;
        data_ = new T[capacity_];
    }

    /** basic_vector(const basic_vector)
    * @param rhs The instance of basic_vector to copy from.
    * @return Copies the basic_vector passed as rhs to this basic_vector. 
    */
    basic_vector(const basic_vector &rhs) {
        size_ = rhs.size();
        capacity_ = rhs.capacity();
        data_ = new T[capacity_];
        std::copy(rhs.data_, rhs.data_ + size_, data_);
    }

    /** operator=(const basic_vector)
    * @param rhs The instance of basic_vector to copy from.
    * @return Returns the pointer to this basic_vector after replacing this basic_vector's contents with the contents of an already existing basic_vector object (rhs).
    */
    basic_vector& operator=(const basic_vector &rhs) {
        size_ = rhs.size();
        capacity_ = rhs.capacity();
        data_ = new T[capacity_];
        std::copy(rhs.data_, rhs.data_ + size_, data_);
        return *this;
    }
    // Size Methods

    /** size()
    * @param None.
    * @return size_t of the current size of data in the data array.
    */
    size_t size() const {
        return size_;
    }

    /** max_size()
    * @param None.
    * @return size_t of the maximum size of data in the data array.
    */
    size_t max_size() const {
        return pow(2, 32)/sizeof(T) - 1;
    }

    /** capacity()
    * @param None.
    * @return size_t of the capacity of the data array.
    */
    size_t capacity() const {
        return capacity_;
    }

    /** resize(size_t)
    * @param n Size to resize the vector to.
    * @return None.
    * @see resize(size_t, const T&)
    */
    void resize(size_t n) {
        resize(n, T());
    }

    /** resize(size_t, const T&)
    * @brief Resizes teh vector to size of n.
    * If n is smaller than the current data array size, then we resize the data array to n and capacity=size=n
    * If n is greater than current data array size, expand capacity to n and default initialize elements after existing size
    * If n is greater than capacity, capacity=n
    * 
    * @param n size to resize the array to.
    * @param val value to default initialize empty array indexes to.
    * @return size_t of the capacity of the data array.
    */
    void resize(size_t n, const T &val) {
        if (size_ == n || (n < capacity_ && n > size_)) // If current size = n or (if n is less than capacity and greater than size) return without doing anything 
            return;

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

        delete[] data_; // Deallocates old data array
        data_ = new_data; // Sets data array pointer to the new data array
    }

    /** empty()
    * @return If size of data is zero, return true, else false.
    */
    bool empty() {
        return size_ == 0;
    }

    /** reserve(size_t)
    * @brief Resize the capacity of the array to n.
    * If n is greater than the max size, we set the capacity to the max size.
    * If n is greater than the capacity, we resize the capacity to n.
    * Do nothing if the size is less than or equal to capacity. 
    * @param n Size to increase capacity by.
    * @see resize(size_t, const T&)
    */
    void reserve(size_t n) {
        if (n > max_size()) {
            resize(max_size());
        } else if (n > capacity_) {
            resize(n);
        }
    }

    /** shrink_to_fit()
    * @brief If the size is not equal to the capacity,
    *   we set the capacity to the size and copy all elements of the existing data array to a new array with a capacity of size.
    */
    void shrink_to_fit() {
        if (size_ != capacity_) {
            capacity_ = size_;
            T* arr = new T[size_];
            std::copy(data_, data_ + size_, arr);
            delete[] data_;
            data_ = arr;
        }
    }
    
    // Element Access
    
    /** operator[](size_t)
    * @brief Unsafe, use at(size_t) for safety
    * Non const
    * @param n index of data to return
    * @return reference to data at index n
    */
    T& operator[](size_t n) {
        return data_[n];
    }

    /** operator[](size_t)
    * @brief Unsafe, use at(size_t) for safety
    * const
    * @param n index of data to return
    * @return reference to data at index n
    */
    const T& operator[](size_t n) const {
        return data_[n];
    }

    /** at(size_t)
    * @brief Return the data at the index in the data array, throws range_error if out of bounds
    * @param n index of data to return
    * @return reference to data at index n
    */
    T& at(size_t n) {
        if (n < 0 || n > size_) {
            throw std::range_error("Invalid index");
        }
        return data_[n];
    }

    /** front()
    * @brief Returns the element at the front of the data array.
    * If data array is empty, throws range error.
    * @return reference to element at the front (index 0)
    */
    T& front() {
        if (size_ == 0) {
            throw std::range_error("Cannot return front since basic_vector has no elements.");
        }
        return data_[0];
    }

    /** back()
    * @brief Returns the element at the end of the data array.
    * If data array is empty, throws range error.
    * @return reference to element at the end (size - 1)
    */
    T& back() {
        if (size_ == 0) {
            throw std::range_error("Cannot return front since basic_vector has no elements.");
        }
        return data_[size_ - 1];
    }
    
    /** data()
    * @return reference to the data array
    */
    T* data() {
        return data_;
    }

    // Modifiers

    /** push_back(const T&)
    * @brief Adds an element to the end of the data array, expands the array if the size exceeds the capacity.
    * @param val Element to add to the array.
    */
    void push_back(const T& val) { // Puts the element val onto the end of the vector, reallocating as necessary.
        if (size_ == capacity_) {
            capacity_ *= 2;
            resize(capacity_);
        }
        
        data_[size_++] = val;
    }

    /** pop_back()
    * @brief Removes the last element of the vector reducing size by one
    */
    void pop_back() {
        data_[size_ - 1] = T();
        size_--;;
    }

    /** pop_back(basic_vector&)
    * @brief Swaps the contents of this basic_vector and another basic_vector
    * @param other basic_vector to swap contents with
    */
    void swap(basic_vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    /** clear()
    * @brief Clears the contents of the array and sets size to 0.
    */
    void clear() {
        std::fill(data_, data_ + capacity_, T());
        size_ = 0;
    }

    /** operator<<(std::ostream&, const basic_vector&)
    * @brief To string method that outputs the size of the array and the contents of the array.
    * @return the ostream containing the tostring output of this basic_vector.
    */
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