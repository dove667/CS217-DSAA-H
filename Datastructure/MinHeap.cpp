#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

class MinHeap {
 private:
	vector<int> heap_;

	static size_t parent(size_t idx) { return (idx - 1) / 2; }
	static size_t left(size_t idx) { return idx * 2 + 1; }
	static size_t right(size_t idx) { return idx * 2 + 2; }

	void sift_up(size_t idx) {
		while (idx > 0) {
			size_t p = parent(idx);
			if (heap_[p] <= heap_[idx]) break;
			swap(heap_[p], heap_[idx]);
			idx = p;
		}
	}

	void sift_down(size_t idx) {
		size_t n = heap_.size();
		while (true) {
			size_t l = left(idx);
			size_t r = right(idx);
			size_t smallest = idx;
			if (l < n && heap_[l] < heap_[smallest]) smallest = l;
			if (r < n && heap_[r] < heap_[smallest]) smallest = r;
			if (smallest == idx) break;
			swap(heap_[idx], heap_[smallest]);
			idx = smallest;
		}
	}

	void ensure_index(size_t idx) const {
		if (idx >= heap_.size()) {
			throw out_of_range("index out of range");
		}
	}

 public:
	MinHeap() = default;
	explicit MinHeap(const vector<int>& arr) { build(arr); }

	void build(const vector<int>& arr) {
		heap_ = arr;
		if (heap_.empty()) return;
		for (int i = static_cast<int>(heap_.size() / 2) - 1; i >= 0; --i) {
			sift_down(static_cast<size_t>(i));
		}
	}

	void push(int value) {
		heap_.push_back(value);
		sift_up(heap_.size() - 1);
	}

	int top() const {
		if (heap_.empty()) throw runtime_error("heap is empty");
		return heap_.front();
	}

	void pop() {
		if (heap_.empty()) throw runtime_error("heap is empty");
		heap_.front() = heap_.back();
		heap_.pop_back();
		if (!heap_.empty()) sift_down(0);
	}

	void replace_top(int value) {
		if (heap_.empty()) {
			heap_.push_back(value);
		} else {
			heap_.front() = value;
			sift_down(0);
		}
	}

	void decrease_key(size_t idx, int new_value) {
		ensure_index(idx);
		if (new_value > heap_[idx]) throw invalid_argument("new value is larger");
		heap_[idx] = new_value;
		sift_up(idx);
	}

	void increase_key(size_t idx, int new_value) {
		ensure_index(idx);
		if (new_value < heap_[idx]) throw invalid_argument("new value is smaller");
		heap_[idx] = new_value;
		sift_down(idx);
	}

	bool erase(size_t idx) {
		if (idx >= heap_.size()) return false;
		increase_key(idx, numeric_limits<int>::max());
		pop();
		return true;
	}

	bool erase_value(int value) {
		for (size_t i = 0; i < heap_.size(); ++i) {
			if (heap_[i] == value) {
				return erase(i);
			}
		}
		return false;
	}

	size_t size() const { return heap_.size(); }
	bool empty() const { return heap_.empty(); }
	void clear() { heap_.clear(); }

	vector<int> data() const { return heap_; }

	ptrdiff_t find_first(int value) const {
		for (size_t i = 0; i < heap_.size(); ++i) {
			if (heap_[i] == value) return static_cast<ptrdiff_t>(i);
		}
		return -1;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	MinHeap h({5, 3, 8, 1, 2, 9});
	auto check_min = [](const MinHeap& heap) {
		if (heap.empty()) return;
		vector<int> raw = heap.data();
		int mn = raw[0];
		for (int v : raw) mn = min(mn, v);
		assert(heap.top() == mn);
	};

	check_min(h);
	assert(h.size() == 6);

	h.push(0);
	assert(h.top() == 0);
	assert(h.size() == 7);

	h.pop();
	assert(h.top() == 1);
	assert(h.size() == 6);

	auto idx = h.find_first(8);
	assert(idx >= 0);
	h.decrease_key(static_cast<size_t>(idx), -2);
	assert(h.top() == -2);
	check_min(h);

	idx = h.find_first(9);
	assert(idx >= 0);
	h.increase_key(static_cast<size_t>(idx), 15);
	assert(h.top() == -2);
	check_min(h);

	h.replace_top(4);
	check_min(h);
	h.erase_value(15);
	assert(h.size() == 5);

	idx = h.find_first(4);
	if (idx >= 0) {
		h.erase(static_cast<size_t>(idx));
	}
	check_min(h);

	vector<int> ordered;
	while (!h.empty()) {
		ordered.push_back(h.top());
		h.pop();
	}
	for (size_t i = 1; i < ordered.size(); ++i) {
		assert(ordered[i - 1] <= ordered[i]);
	}

	cout << "All heap tests passed.\n";
	return 0;
}
