#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list() {
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        T data = list.getHead()->data;
        list.RemoveHead();
        return data;
    }
    T popBack() override {
        T data = list.getTail()->data;
        list.RemoveTail();
        return data;
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead()->data;
    }
    const T& back() const override {
        return list.getTail()->data;
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






