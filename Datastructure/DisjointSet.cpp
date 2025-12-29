#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class DisjointSet {
 private:
    vector<int> S; // Negative size for roots, parent index for others

    void ensure_index(int x) const {
        if (x < 0 || x >= static_cast<int>(S.size())) {
            throw out_of_range("index out of range");
        }
    }

 public:
    explicit DisjointSet(size_t n) : S(n, -1) {}

    int find(int x) {
        ensure_index(x);
        if (S[x] < 0) {
            return x;
        }
        else{
            S[x] = find(S[x]); // Path compression
            return S[x];
        }
    }

    void unite(int x, int y) {
        ensure_index(x);
        ensure_index(y);
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y) {
            if (S[root_x] > S[root_y]) { // Union by size
                swap(root_x, root_y);
            }
            S[root_x] += S[root_y];
            S[root_y] = root_x;
        }
    }

    int get_size(int x) {
        int root = find(x);
        return -S[root]; // Convert negative to positive
    }

    bool is_connected(int x, int y) {
        try {
            return find(x) == find(y);
        } catch (const out_of_range&) {
            return false;
        }
    }

    size_t total_elements() const { return S.size(); }

    int count_components() const {
        int count = 0;
        for (int i = 0; i < static_cast<int>(S.size()); ++i) {
            if (S[i] < 0) {
                count++;
            }
        }
        return count;
    }

    vector<int> internal_state() const { return S; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Test 1: Initialization
    DisjointSet ds(5);
    assert(ds.count_components() == 5);
    assert(ds.total_elements() == 5);

    // Test 2: Each element is in its own set initially
    for (int i = 0; i < 5; ++i) {
        assert(ds.find(i) == i);
        assert(ds.get_size(i) == 1);
    }

    // Test 3: Simple union
    ds.unite(0, 1);
    assert(ds.is_connected(0, 1));
    assert(ds.count_components() == 4);

    // Test 4: Get component size
    assert(ds.get_size(0) == 2);
    assert(ds.get_size(1) == 2);

    // Test 5: Path compression and union transitivity
    ds.unite(2, 3);
    ds.unite(0, 2);
    assert(ds.is_connected(1, 3));
    assert(ds.count_components() == 2);
    assert(ds.get_size(0) == 4);

    // Test 6: Large component
    ds.unite(1, 4);
    assert(ds.is_connected(0, 4));
    assert(ds.count_components() == 1);
    assert(ds.get_size(0) == 5);

    // Test 7: Path compression - multiple find calls
    for (int i = 0; i < 5; ++i) {
        assert(ds.find(i) == ds.find(0)); // All should have same root
    }

    // Test 8: Boundary check - out of range
    DisjointSet ds2(3);
    try {
        ds2.find(-1);
        assert(false && "Should throw out_of_range");
    } catch (const out_of_range&) {
        // Expected
    }

    try {
        ds2.find(3);
        assert(false && "Should throw out_of_range");
    } catch (const out_of_range&) {
        // Expected
    }

    try {
        ds2.unite(0, 5);
        assert(false && "Should throw out_of_range");
    } catch (const out_of_range&) {
        // Expected
    }

    // Test 9: Union by size optimization (smaller component attaches to larger)
    DisjointSet ds3(4);
    ds3.unite(0, 1);
    ds3.unite(2, 3);
    assert(ds3.count_components() == 2);
    ds3.unite(0, 2);
    // After union, all should be connected
    for (int i = 1; i < 4; ++i) {
        assert(ds3.is_connected(0, i));
    }
    assert(ds3.count_components() == 1);

    cout << "All DisjointSet tests passed.\n";
    return 0;
}