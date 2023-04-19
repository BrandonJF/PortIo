#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <vector>

template<typename T>
class CircularQueue {
public:
    CircularQueue(size_t size) {
        m_size = size;
        m_data = new T[size];
        m_head = 0;
        m_tail = 0;
        m_count = 0;
    }

    ~CircularQueue() {
        delete[] m_data;
    }

    void enqueue(const T& value) {
        if (m_count == m_size) {
            m_data[m_head] = value;
            m_head = (m_head + 1) % m_size;
            m_tail = (m_tail + 1) % m_size;
        } else {
            m_data[m_tail] = value;
            m_tail = (m_tail + 1) % m_size;
            m_count++;
        }
    }

    T dequeue() {
        if (m_count == 0) {
            throw std::out_of_range("queue is empty");
        }
        T value = m_data[m_head];
        m_head = (m_head + 1) % m_size;
        m_count--;
        return value;
    }

    T peek() const {
        if (m_count == 0) {
            throw std::out_of_range("queue is empty");
        }
        return m_data[m_head];
    }

    T peekAt(size_t index) const {
        if (index >= m_count) {
            throw std::out_of_range("index out of range");
        }
        return m_data[(m_head + index) % m_size];
    }

    bool isEmpty() const {
        return m_count == 0;
    }

    bool isFull() const {
        return m_count == m_size;
    }

    size_t size() const {
        return m_count;
    }

    std::vector<T> toList() const {
        std::vector<T> vec;
        vec.reserve(m_count);
        for (size_t i = 0; i < m_count; i++) {
            vec.push_back(m_data[(m_head + i) % m_size]);
        }
        return vec;
    }

    bool operator==(const std::vector<T>& vec) const {
        if (m_count != vec.size()) {
            return false;
        }
        for (size_t i = 0; i < m_count; i++) {
            if (m_data[(m_head + i) % m_size] != vec[i]) {
                return false;
            }
        }
        return true;
    }

private:
    T* m_data;
    size_t m_size;
    size_t m_head;
    size_t m_tail;
    size_t m_count;
};
#endif