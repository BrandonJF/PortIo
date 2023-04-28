#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <vector>

template<typename T>
class CircularQueue {

public:
    CircularQueue();
    explicit CircularQueue(size_t size);

    void enqueue(const T& value);

    T dequeue();

    T peek() const;

    T peekAt(size_t index) const;

    bool isEmpty() const;

    bool isFull() const;

    size_t size() const;

    std::vector<T> toList() const;

    bool operator==(const std::vector<T>& vec) const;

private:
    T* m_data = nullptr;
    size_t m_size = 0;
    size_t m_head = 0;
    size_t m_tail = 0;
    size_t m_count = 0;
};
#endif