#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class SinglyLinkedList {
 private:
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;

 public:
    SinglyLinkedList() = default;
    ~SinglyLinkedList() { clear(); }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    void clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void insert(size_t pos, const T& value) {
        if (pos > size_) {
            throw out_of_range("insert position out of range");
        }
        Node* node = new Node(value);
        if (pos == 0) {
            node->next = head_;
            head_ = node;
            if (!tail_) {
                tail_ = node;
            }
        } else {
            Node* prev = head_;
            for (size_t i = 1; i < pos; ++i) {
                prev = prev->next;
            }
            node->next = prev->next;
            prev->next = node;
            if (prev == tail_) {
                tail_ = node;
            }
        }
        ++size_;
    }

    bool erase(size_t pos) {
        if (pos >= size_) {
            return false;
        }
        Node* removed = nullptr;
        if (pos == 0) {
            removed = head_;
            head_ = head_->next;
            if (!head_) {
                tail_ = nullptr;
            }
        } else {
            Node* prev = head_;
            for (size_t i = 1; i < pos; ++i) {
                prev = prev->next;
            }
            removed = prev->next;
            prev->next = removed->next;
            if (removed == tail_) {
                tail_ = prev;
            }
        }
        delete removed;
        --size_;
        return true;
    }

    bool contains(const T& value) const {
        Node* cur = head_;
        while (cur) {
            if (cur->value == value) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void for_each(const function<void(const T&)>& fn) const {
        Node* cur = head_;
        while (cur) {
            fn(cur->value);
            cur = cur->next;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SinglyLinkedList<int> lst;
    assert(lst.empty());

    lst.insert(0, 1);  // [1]
    lst.insert(1, 3);  // [1, 3]
    lst.insert(1, 2);  // [1, 2, 3]
    assert(lst.size() == 3);
    assert(lst.contains(2));
    assert(!lst.contains(10));

    lst.erase(1);  // remove 2 -> [1, 3]
    assert(lst.size() == 2);
    assert(!lst.contains(2));

    lst.insert(lst.size(), 4);  // append -> [1, 3, 4]
    lst.insert(0, 0);           // prepend -> [0, 1, 3, 4]
    vector<int> values;
    lst.for_each([&](int value) { values.push_back(value); });
    assert((values == vector<int>{0, 1, 3, 4}));

    assert(lst.erase(0));              // remove head -> [1, 3, 4]
    assert(lst.erase(lst.size() - 1)); // remove tail -> [1, 3]
    assert(!lst.erase(5));             // out of range -> unchanged

    lst.clear();
    for (int i = 0; i < 10; ++i) {
        lst.insert(lst.size(), i);
    }
    int sum = 0;
    lst.for_each([&](int value) { sum += value; });
    assert(sum == 45);

    lst.clear();
    assert(lst.empty());

    cout << "SinglyLinkedList demo finished.\n";
    return 0;
}
