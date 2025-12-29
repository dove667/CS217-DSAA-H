#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <class T>
class SimpleQueue {
 private:
    vector<T> buffer_;
    size_t head_ = 0;

    void cleanup() {
        if (head_ > 0 && head_ * 2 >= buffer_.size()) {
            buffer_.erase(buffer_.begin(), buffer_.begin() + static_cast<long>(head_));
            head_ = 0;
        }
    }

 public:
    SimpleQueue() = default;

    bool empty() const { return size() == 0; }

    size_t size() const { return buffer_.size() - head_; }

    void clear() {
        buffer_.clear();
        head_ = 0;
    }

    void enqueue(const T& value) { buffer_.push_back(value); }

    void dequeue() {
        if (empty()) {
            throw runtime_error("queue is empty");
        }
        ++head_;
        cleanup();
    }

    const T& front() const {
        if (empty()) {
            throw runtime_error("queue is empty");
        }
        return buffer_[head_];
    }

    const T& back() const {
        if (empty()) {
            throw runtime_error("queue is empty");
        }
        return buffer_.back();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SimpleQueue<int> q;
    assert(q.empty());

    for (int i = 0; i < 5; ++i) {
        q.enqueue(i);
    }
    assert(q.size() == 5);
    assert(q.front() == 0);
    assert(q.back() == 4);

    q.dequeue();
    q.dequeue();
    assert(q.front() == 2);
    assert(q.size() == 3);

    q.enqueue(5);
    q.enqueue(6);
    assert(q.back() == 6);
    assert(q.size() == 5);

    while (!q.empty()) {
        q.dequeue();
    }
    assert(q.empty());

    cout << "SimpleQueue demo finished.\n";
    return 0;
}
