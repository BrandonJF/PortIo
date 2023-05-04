#pragma once
#include <iostream>
#include <vector>
#include <memory>

//create a constructor for the circular queue

template<typename T>
class CircularQueue {

private:
    std::unique_ptr<T[]> m_data;
    size_t m_size = 0;
    size_t m_head = 0;
    size_t m_tail = 0;
    size_t m_count = 0;

public:
    CircularQueue();
    CircularQueue(size_t size);
    void enqueue(const T& value);
    T dequeue();
    T peek() const;
    T peekAt(size_t index) const;
    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;
    std::vector<T> toList() const;
    bool operator==(const std::vector<T>& vec) const;
};  
