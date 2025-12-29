#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cstdint>
#include <cmath>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int count;
    int subnodes;        // 子树总元素数（含重复）
    explicit Node(int k)
    : key(k), left(nullptr), right(nullptr), height(1), count(1), subnodes(1) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

int nodeSize(Node* node) {
    return node ? node->subnodes : 0;
}

void updateSize(Node* node) {
    if (node) {
        node->subnodes = node->count + nodeSize(node->left) + nodeSize(node->right);
    }
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateSize(y);

    updateHeight(x);
    updateSize(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateSize(x);

    updateHeight(y);
    updateSize(y);
    return y;
}

Node* reBalance(Node *node) {
    int balance = getBalance(node);
    if (balance > 1) {
        // LL Case
        if (getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        // LR Case
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1) {
        // RR Case
        if (getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        // RL Case
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else {
        node->count++;
        updateSize(node);
        return node;
    }
    updateHeight(node);
    updateSize(node);
    return reBalance(node);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// 用于删除整棵树中“键等于 key 的那个节点”（无视其 count，整节点移除）
Node* removeAll(Node* root, int key) {
    if (!root) return root;
    if (key < root->key)
        root->left = removeAll(root->left, key);
    else if (key > root->key)
        root->right = removeAll(root->right, key);
    else {
        // 不考虑 count，直接删除这个节点
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                delete root;
                return nullptr;
            }
            *root = *temp;
            delete temp;
        } else {
            // 有两个子节点：用右子树最小节点替换并继续删除那个节点（完整删除）
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->count = temp->count;
            root->right = removeAll(root->right, temp->key);
        }
    }
    updateHeight(root);
    updateSize(root);
    return reBalance(root);
}

Node* remove(Node* root, int key) {
    if (!root) return root;
    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else {
        if (root->count > 1) {
            root->count--;
            updateSize(root);
        }
        else {
            if (!root->left || !root->right) { // 只有一个子节点或无子节点
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp; // 拷贝内容
                delete temp;
            } else {
                // 有两个子节点：拷贝后继的 key 和 count，完整删除后继节点
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->count = temp->count;
                root->right = removeAll(root->right, temp->key);
            }
        }
    }
    if (!root) return root;
    updateHeight(root);
    updateSize(root);
    return reBalance(root);
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

int rankLess(Node* node, int key) {
    if (!node) return 0;
    if (key < node->key) {
        return rankLess(node->left, key);
    }
    if (key == node->key) { // 找到相等的节点
        return nodeSize(node->left);
    }
    // key > node->key
    return nodeSize(node->left) + node->count + rankLess(node->right, key);
}

int kth(Node* node, int k) {
    while (node) {
        int leftSize = nodeSize(node->left);
        if (k <= leftSize) {
            node = node->left;
        } else if (k <= leftSize + node->count) {
            return node->key;
        } else { // k > leftSize + node->count
            k = k - leftSize - node->count;
            node = node->right;
        }
    }
    return -1; // 不存在
}
// the predecessor is the largest number strictly smaller than key
int predecessor(Node* node, int key) {
    int maxPredecessor = numeric_limits<int>::min(); //目前最大前驱
    while (node) {
        if (key <= node->key) {
            node = node->left;
        } else {
            maxPredecessor = node->key;
            node = node->right;
        }
    }
    return maxPredecessor;
}
// the successor is the smallest number strictly larger than key
int successor(Node* node, int key) {
    int minSuccessor = numeric_limits<int>::max(); //目前最小后继
    while (node) {
        if (key >= node->key) {
            node = node->right;
        } else {
            minSuccessor = node->key;
            node = node->left;
        }
    }
    return minSuccessor;
}

void preorder(Node* root, std::vector<int>& list) {
    if (!root) return;
    list.push_back(root->key);
    preorder(root->left, list);
    preorder(root->right, list);
}

uint32_t checkSum(Node* root) {
    std::vector<int> preorderKeys;
    preorder(root, preorderKeys);
    uint32_t result = 0;
    for (int i = 1; i <= static_cast<int>(preorderKeys.size()); ++i) {
        int v = preorderKeys[i - 1];
        if (v < 0) v = -v;
        auto aval = static_cast<uint32_t>(v);
        result += (static_cast<uint32_t>(i) ^ aval) % (1ULL << 32);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    Node* root = nullptr;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            root = insert(root, x);
        } else if (op == 2) {
            root = remove(root, x);
        } else if (op == 3) {
            cout << rankLess(root, x) + 1 << '\n';
        } else if (op == 4) {
            cout << kth(root, x) << '\n';
        } else if (op == 5) {
            cout << predecessor(root, x) << '\n';
        } else if (op == 6) {
            cout << successor(root, x) << '\n';
        }
    }
    cout << checkSum(root) << '\n';
    return 0;
}
