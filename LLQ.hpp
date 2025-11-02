#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list(){
    }

    // Insertion
    void enqueue(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getHead()) {
            T data = list.getHead()->data;
            list.RemoveHead();
            return data;
        }
        throw std::runtime_error("Attempted to get null data");

    }

    // Access
    T peek() const override {
        if (list.getHead()) {
            return list.getHead()->data;
        }
        throw std::runtime_error("Attempted to get null data");
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};