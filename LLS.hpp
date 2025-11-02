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
    LLS() : list() {
    }

    // Insertion
    void push(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T pop() override {
        if (list.getTail()) {
            T data = list.getTail()->data;
            list.RemoveTail();
            return data;
        }
        throw std::runtime_error("Attempted to get null data");
    }

    // Access
    T peek() const override {
        if (list.getTail()) {
            return list.getTail()->data;
        }
        throw std::runtime_error("Attempted to get null data");
    }

    //Getters
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};