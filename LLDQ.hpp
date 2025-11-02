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
    LLDQ() {
        list = new LinkedList<T>{};
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
        return list.RemoveHead()->data;
    }
    T popBack() override {
        return list.RemoveTail()->data;
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






