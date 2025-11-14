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
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getHead()) {
            T data = list.getHead()->data;
            list.removeHead();
            return data;
        }
        throw std::runtime_error("Attempted to get null data");
    }
    T popBack() override {
        if (list.getTail()) {
            T data = list.getTail()->data;
            list.removeTail();
            return data;
        }
        throw std::runtime_error("Attempted to get null data");
    }

    // Element Accessors
    const T& front() const override {
        if (list.getHead()) {
            return list.getHead()->data;
        }
        throw std::runtime_error("Attempted to get null data");
    }
    const T& back() const override {
        if (list.getTail()) {
            return list.getTail()->data;
        }
        throw std::runtime_error("Attempted to get null data");
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






