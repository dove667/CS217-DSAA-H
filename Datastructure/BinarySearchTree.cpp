#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class binary_search_tree {
 private:
    struct bst_node {
        int key;                         
        bst_node *left;
        bst_node *right;
        bst_node *parent;
        explicit bst_node(int _value) 
        : key(_value), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    bst_node *root_;
    std::size_t size_;
    void delete_subtree(bst_node *node) {
        if (!node) return;
        delete_subtree(node->left);
        delete_subtree(node->right);
        delete node;
    }
    int minimum(bst_node *node) {
        while (node->left) {
            node = node->left;
        }
        return node->key;
    }

    int maximum(bst_node *node) {
        while (node->right) {
            node = node->right;
        }
        return node->key;
    }
    int tree_search(bst_node *x, int k) {
        if (!x || k == x->key) {
            return x ? x->key : -1;
        }
        if (k < x->key) {
            return tree_search(x->left, k);
        } else return tree_search(x->right, k);
    }
 public:
    binary_search_tree() {
        root_ = nullptr;
        size_ = 0;
    }
    ~binary_search_tree() {
        delete_subtree(root_);
        root_ = nullptr;
        size_ = 0;
    }

    int minimum_root() { return root_ ? minimum(root_) : -1; }

    int maximum_root() { return root_ ? maximum(root_) : -1; }

    int successor(bst_node *node) {
        if (node->right) {
            return minimum(node->right);
        }
        else{
            bst_node *y = node->parent;
        while (y && node == y->right) {
            node = y;
            y = y->parent;
        }
        return y ? y->key : -1;
        }
    }

    int tree_search_root(int k) {
        return tree_search(root_, k);
    }

    void insert(int key) {
        bst_node *node = new bst_node(key);
        bst_node *x = root_;
        bst_node *y = nullptr;
        while (x) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        node->parent = y;
        if (!y) {
            root_ = node;
        } else if (node->key < y->key) {
            y->left = node;
        } else {
            y->right = node;
        }
        size_++;
    }
    void transplant(bst_node *u, bst_node *v) {
        if (!u->parent) {
            root_ = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v) {
            v->parent = u->parent;
        }
    }
    void remove(int key) {
        bst_node *node = root_;
        while (node && node->key != key) {
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        if (!node) return; // Key not found
        if (!node->left) {
            transplant(node, node->right);
        } else if (!node->right) {
            transplant(node, node->left);
        } else {
            bst_node *y = node->right;
            while (y->left) {
                y = y->left;
            }
            if (y != node->right) {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
        }
        size_--;
        delete node;
    }
    
    std::size_t size() { return size_; }
    
    
    void traverse_inorder(std::function<void(int)> callback,
                          bst_node *node) {
        if (!node) {
            return;
        }
        traverse_inorder(callback, node->left);
        callback(node->key);
        traverse_inorder(callback, node->right);
    }

    void traverse_preorder(std::function<void(int)> callback,
                           bst_node *node) {
        if (!node) {
            return;
        }
        callback(node->key);
        traverse_preorder(callback, node->left);
        traverse_preorder(callback, node->right);
    }

    void traverse_postorder(std::function<void(int)> callback,
                            bst_node *node) {
        if (!node) {
            return;
        }
        traverse_postorder(callback, node->left);
        traverse_postorder(callback, node->right);
        callback(node->key);
    }

    std::vector<int> get_elements_inorder() {
        std::vector<int> result;
        traverse_inorder([&](int node_value) { result.push_back(node_value); },
                         root_);
        return result;
    }

    std::vector<int> get_elements_preorder() {
        std::vector<int> result;
        traverse_preorder([&](int node_value) { result.push_back(node_value); },
                          root_);
        return result;
    }

    std::vector<int> get_elements_postorder() {
        std::vector<int> result;
        traverse_postorder([&](int node_value) { result.push_back(node_value); },
                           root_);
        return result;
    }
};

bool equal_vectors(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    return lhs == rhs;
}

void assert_true(bool condition, const std::string &message) {
    if (!condition) {
        throw std::runtime_error("Test failed: " + message);
    }
}

void run_basic_scenario() {
    binary_search_tree bst;

    // Build a balanced-ish tree.
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    assert_true(bst.size() == 7, "size after insertions");
    assert_true(bst.tree_search_root(7) == 7, "search existing key");
    assert_true(bst.tree_search_root(99) == -1, "search missing key");

    std::vector<int> expected_inorder{3, 5, 7, 10, 12, 15, 18};
    std::vector<int> expected_preorder{10, 5, 3, 7, 15, 12, 18};
    std::vector<int> expected_postorder{3, 7, 5, 12, 18, 15, 10};

    assert_true(equal_vectors(bst.get_elements_inorder(), expected_inorder),
                "inorder traversal");
    assert_true(equal_vectors(bst.get_elements_preorder(), expected_preorder),
                "preorder traversal");
    assert_true(equal_vectors(bst.get_elements_postorder(), expected_postorder),
                "postorder traversal");

    assert_true(bst.minimum_root() == 3, "minimum value");
    assert_true(bst.maximum_root() == 18, "maximum value");

    // Remove leaf node.
    bst.remove(3);
    std::vector<int> expected_after_leaf_removal{5, 7, 10, 12, 15, 18};
    assert_true(bst.size() == 6, "size after removing leaf");
    assert_true(equal_vectors(bst.get_elements_inorder(), expected_after_leaf_removal),
                "inorder after leaf removal");

    // Remove node with two children (root replacement path).
    bst.remove(10);
    std::vector<int> expected_after_root_removal{5, 7, 12, 15, 18};
    assert_true(bst.size() == 5, "size after removing root with two children");
    assert_true(equal_vectors(bst.get_elements_inorder(), expected_after_root_removal),
                "inorder after root removal");
    assert_true(bst.minimum_root() == 5, "minimum after removals");
    assert_true(bst.maximum_root() == 18, "maximum after removals");

    // Remove a missing key should not change size.
    bst.remove(42);
    assert_true(bst.size() == 5, "size unchanged after removing missing key");
    std::vector<int> expected_preorder_after_removals{12, 5, 7, 15, 18};
    std::vector<int> expected_postorder_after_removals{7, 5, 18, 15, 12};
    assert_true(equal_vectors(bst.get_elements_preorder(), expected_preorder_after_removals),
                "preorder after removals");
    assert_true(equal_vectors(bst.get_elements_postorder(), expected_postorder_after_removals),
                "postorder after removals");
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    run_basic_scenario();
    std::cout << "All BST tests passed.\n";
    return 0;
}