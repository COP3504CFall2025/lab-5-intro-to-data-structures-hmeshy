#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {
        list = new LinkedList<T>{};
    }

    // Insertion
    void push(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T pop() override {
        return list.RemoveTail()->data;
    }

    // Access
    T peek() const override {
        return list.getTail()->data;
    }

    //Getters
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};