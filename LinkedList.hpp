#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		if (head != nullptr) {
			Node<T>* front = head;
			while (front->next != nullptr) {
				std::cout << front->data << std::endl;
				front = front->next;
			}
			std::cout << front->data << std::endl;
		}
	}
	void PrintReverse() const {
		if (tail != nullptr) {
			Node<T>* back = tail;
			while (back->prev != nullptr) {
				std::cout << back->data << std::endl;
				back = back->prev;
			}
			std::cout << back->data << std::endl;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}

	Node<T>* getHead() {return head;}
	const Node<T>* getHead() const {return head;}
	Node<T>* getTail() {return tail;}
	const Node<T>* getTail() const {return tail;}

	// Insertion
	void AddHead(const T& data) {
		Node<T>* new_head = new Node<T>{data, nullptr, head};
		count++;
		if (head != nullptr) {
			head->prev = new_head;
		}
		head = new_head;
		if (count == 1) {
			tail = new_head;
		}
	}
	void AddTail(const T& data) {
		if (count == 0) {
			AddHead(data);
		}
		else {
			Node<T>* new_tail = new Node<T>{data, tail, nullptr};
			count++;
			if (tail != nullptr) {
				tail->next = new_tail;
			}
			tail = new_tail;
		}
	}


	// Removal
	bool RemoveHead() {
		if (head == nullptr) {
			return false; // only remove head if head exists
		}
		if (count == 1) { // special case - the only element is the head & tail
			delete head;
			// no need to adjust next/prev, both should be nullptr
			tail = nullptr;
			head = nullptr;
			count--;
			return true;
		}
		Node<T>* new_head = head->next;
		count--;
		new_head->prev = nullptr;
		delete head;
		head->next = nullptr;
		head = new_head;
		return true;
	}
	bool RemoveTail() {
		if (tail == nullptr) {
			return false; // only remove head if head exists
		}
		if (count == 1) { // special case - the only element is the head & tail
			return RemoveHead(); // these are equivalent in this case - why write extra code?
		}
		Node<T>* new_tail = tail->prev;
		count--;
		new_tail->next = nullptr;
		delete tail;
		tail->next = nullptr;
		tail = new_tail;
		return true;
	};
	void Clear() {
		while (head != nullptr) {
			RemoveHead();
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) return *this;
		Clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) return *this;
		Clear();
		count = 0;
		head = nullptr;
		tail = nullptr;
		Node<T>* other_node = rhs.head;
		while (other_node != nullptr) {
			AddTail(other_node->data);
			other_node = other_node->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		count = 0;
		head = nullptr;
		tail = nullptr;
		Node<T>* other_node = list.head;
		while (other_node != nullptr) {
			AddTail(other_node->data);
			other_node = other_node->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept
	{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


