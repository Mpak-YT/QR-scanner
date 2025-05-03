#pragma once
#include <iostream>
#include <stdexcept>
#include "InvalidIndex.h"

template<typename T>
class MyQueue {
public:
    MyQueue() : front_(nullptr), back_(nullptr), size_(0) {}

    ~MyQueue() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            front_ = back_ = newNode;
        }
        else {
            back_->next = newNode;
            back_ = newNode;
        }
        ++size_;
    }

    void pop() {
        if (empty()) {
            throw "empty";
        }
        Node* temp = front_;
        front_ = front_->next;
        delete temp;
        --size_;
        if (empty()) {
            back_ = nullptr;
        }
    }

    T& front() {
        if (empty()) {
            throw "empty";
        }
        return front_->data;
    }

    const T& front() const {
        if (empty()) {
            throw "empty";
        }
        return front_->data;
    }

    std::size_t size() const {
        return size_;
    }

    T operator[](std::size_t index) {
        try 
        {
            if (index >= size_ || index < 0) {
                throw (InvalidIndex("Index out of bounds"));
            }
        }
        catch (InvalidIndex& exception)
        {
            std::cout << exception << std::endl;
            return NULL;
        }
        for (std::size_t i = 0; i < index; i++) {
            push(front());
            pop();
           
        }
        T result = front_->data;
        for (std::size_t i = index; i < size_; i++) {
            push(front());
            pop();
        }
        return result;
    }
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front_;
    Node* back_;
    std::size_t size_;
public:
    class iterator {
    
    public:
        iterator(Node* node) : current_(node) {}

        iterator& operator++() {
            if (current_) current_ = current_->next;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current_ != other.current_;
        }

        T& operator*() const {
            return current_->data;
        }
    private:
        Node* current_;
    };

    iterator begin() {
        return iterator(front_);
    }

    iterator end() {
        return iterator(nullptr);
    }
};