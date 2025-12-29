#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <class T>
class SimpleStack {
 private:
    vector<T> data_;

 public:
    SimpleStack() = default;

    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }

    void clear() { data_.clear(); }

    void push(const T& value) { data_.push_back(value); }

    void pop() {
        if (data_.empty()) {
            throw runtime_error("stack is empty");
        }
        data_.pop_back();
    }

    const T& top() const {
        if (data_.empty()) {
            throw runtime_error("stack is empty");
        }
        return data_.back();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SimpleStack<int> st;

    assert(st.empty());
    st.push(1);
    st.push(2);
    st.push(3);
    assert(st.size() == 3);
    assert(st.top() == 3);

    st.pop();
    assert(st.top() == 2);
    st.pop();
    assert(st.top() == 1);

    st.pop();
    assert(st.empty());

    for (int i = 0; i < 100; ++i) {
        st.push(i);
    }
    assert(st.size() == 100);
    st.clear();
    assert(st.empty());

    cout << "SimpleStack demo finished.\n";
    return 0;
}
