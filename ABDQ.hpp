#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        data_ = new T[4];
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    explicit ABDQ(std::size_t capacity) {
        data_ = new T[capacity];
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        if (back_ - front_ == size_) { // not fully looped
            for (size_t i = front_; i < back_; i++) {
                data_[i] = other.data_[i];
            }
        }
        else {
            for (size_t i = front_; i < capacity_; i++) {
                data_[i] = other.data_;
            }
            for (size_t i = 0; i < back_; i++) {
                data_[i] = other.data_;
            }
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        if (back_ - front_ == size_) { // not fully looped
            for (size_t i = front_; i < back_; i++) {
                data_[i] = other.data_[i];
            }
        }
        else {
            for (size_t i = front_; i < capacity_; i++) {
                data_[i] = other.data_;
            }
            for (size_t i = 0; i < back_; i++) {
                data_[i] = other.data_;
            }
        }
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.curr_size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

    }
    ~ABDQ() override {
        delete[] data_;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }
        if (front_ == 0) {
            front_ = capacity_ - 1;
        }
        else {
            front_--;
        }
        size_++;
        data_[front_] = item;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }
        data_[back_] = item;
        back_++;
        if (back_ == capacity_) {
            back_ = 0;
        }
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            return nullptr;
        }
        T data_t = data_[front_];
        data_[front_] = T{};
        front_++;
        if (front_ == capacity_) {
            front_ = 0;
        }
        size_--;
        if (size_ * 2 < capacity_) {
            shrinkIfNeeded();
        }
        return data_t;
    }
    T popBack() override {
        if (size_ == 0) {
            return nullptr;
        }
        T data_t;
        if (back_ == 0) {
            data_t = data_[capacity_];
            data_[capacity_] = T{};
            back_ = capacity_;
        }
        else {
            data_t = data_[back_-1];
            data_[back_-1] = T{};
            back_--;
        }
        size_--;
        if (size_ * 2 < capacity_) {
            shrinkIfNeeded();
        }
        return data_t;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            return nullptr;
        }
        return data_[front_];
    }
    const T& back() const override {
        if (back_ == 0) {
            return data_[capacity_];
        }
        return data_[back_-1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
