#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    size_t front_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
        array_ = new T[1];
        capacity_ = 1;
        curr_size_ = 0;
        front_ = 0;
    }
    explicit ABQ(const size_t capacity) {
        array_ = new T[capacity];
        capacity_ = capacity;
        curr_size_ = 0;
        front_ = 0;
    }
    ABQ(const ABQ& other) {
        array_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = other.front_;
        for (size_t i = front_; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        array_ = new T[rhs.capacity_];
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_ = rhs.front_;
        for (size_t i = front_; i < curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = other.front_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_ = rhs.front_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    }
    ~ABQ() noexcept override {
        delete[] array_;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Getters
    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ + front_ == capacity_) {
            capacity_ *= scale_factor_;
            T* new_array = new T[capacity_];
            for (size_t i = front_; i < front_ + curr_size_; i++) {
                new_array[i] = array_[i];
            }
            delete[] array_;
            array_ = new_array;
            front_ = 0;
        }
        array_[curr_size_ + front_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        return array_[front_];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ != 0) {
            T val = array_[front_];
            curr_size_--;
            array_[front_] = T{};
            front_++;
            return val;
        }
        throw std::runtime_error("Attempted to get null data");
    }

};
