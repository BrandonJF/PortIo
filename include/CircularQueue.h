#include <iostream>
#include <vector>

template <typename T> class CircularQueue {
public:
    CircularQueue(int capacity) : capacity_(capacity), size_(0), head_(0), tail_(0) {
        buffer_.resize(capacity_);
    }

    void enqueue(const T& value) {
        if (size_ == capacity_) {
            dequeue();
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        size_++;
    }

    T dequeue() {
        if (size_ == 0) {
            std::cerr << "Error: Queue underflow" << std::endl;
            return T();
        }
        T value = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        size_--;
        return value;
    }

    T peek(int index) const {
        if (index >= size_) {
            std::cerr << "Error: Invalid index" << std::endl;
            return T();
        }
        return buffer_[(head_ + index) % capacity_];
    }

    int size() const {
        return size_;
    }

private:
    std::vector<T> buffer_;
    int capacity_;
    int size_;
    int head_;
    int tail_;
};
