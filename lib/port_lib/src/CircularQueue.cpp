#include "CircularQueue.h"
#include <stdexcept>
#include <memory>

template<typename T>
CircularQueue<T>::CircularQueue(size_t size) : m_size(size), m_data(std::unique_ptr<T[]>(new T[size])) {}


template<typename T>
void CircularQueue<T>::enqueue(const T& value) {
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

template<typename T>
T CircularQueue<T>::dequeue() {
    if (m_count == 0) {
        throw std::out_of_range("queue is empty");
    }
    T value = m_data[m_head];
    m_head = (m_head + 1) % m_size;
    m_count--;
    return value;
}

template<typename T>
T CircularQueue<T>::peek() const {
    if (m_count == 0) {
        throw std::out_of_range("queue is empty");
    }
    return m_data[m_head];
}

template<typename T>
T CircularQueue<T>::peekAt(size_t index) const {
    if (index >= m_count) {
        throw std::out_of_range("index out of range");
    }
    return m_data[(m_head + index) % m_size];
}

template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return m_count == 0;
}

template<typename T>
bool CircularQueue<T>::isFull() const {
    return m_count == m_size;
}

template<typename T>
size_t CircularQueue<T>::size() const {
    return m_count;
}

template <typename T>
bool CircularQueue<T>::operator==(const std::vector<T> &vec) const {
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

template<typename T>
std::vector<T> CircularQueue<T>::toList() const {
        std::vector<T> vec;
        vec.reserve(m_count);
        for (size_t i = 0; i < m_count; i++) {
            vec.push_back(m_data[(m_head + i) % m_size]);
        }
        return vec;
    }