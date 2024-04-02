#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

//here is the queue class that holds all of the pointers
//and information needed for the queue to function

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& item) : data(item), next(nullptr) {}
    };
    Node* frontPtr;
    Node* rearPtr;
    int queueSize;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), queueSize(0) {}
    ~Queue() {
        while (!empty())
            pop();
    }
    void push(const T& item) {
        Node* newNode = new Node(item);
        if (empty())
            frontPtr = newNode;
        else
            rearPtr->next = newNode;
        rearPtr = newNode;
        queueSize++;
    }
    void pop() {
        if (empty()) {
            std::cerr << "Queue is empty. Cannot pop.\n";
            return;
        }
        Node* temp = frontPtr;
        frontPtr = frontPtr->next;
        delete temp;
        queueSize--;
        if (frontPtr == nullptr)
            rearPtr = nullptr;
    }
    T front() {
        if (empty()) {
            std::cerr << "Queue is empty. No front element.\n";
            exit(1);
        }
        return frontPtr->data;
    }
    int size() {
        return queueSize;
    }
    bool empty() {
        return queueSize == 0;
    }
    void move_to_rear() {
        if (size() <= 1)
            return;
        T frontElement = front();
        pop();
        push(frontElement);
    }
};

#endif