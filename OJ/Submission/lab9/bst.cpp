#include <iostream>
#include <limits>
using namespace std;

struct Node {
    int key;       // 键值
    int cnt;       // 该键出现次数
    int sz;        // 子树总元素数（含重复）
    Node *left;
    Node *right;
    explicit Node(int k)
        : key(k), cnt(1), sz(1), left(nullptr), right(nullptr) {}
};

int nodeSize(Node* node) {
    return node ? node->sz : 0;
}

void updateSize(Node* node) {
    if (node) {
        node->sz = node->cnt + nodeSize(node->left) + nodeSize(node->right);
    }
}

void insert(Node*& node, int key) {
    if (!node) {
        node = new Node(key);
        return;
    }
    if (key == node->key) {
        node->cnt++;
    } else if (key < node->key) {
        insert(node->left, key);
    } else {
        insert(node->right, key);
    }
    updateSize(node);
}

// 删除整棵中“键等于 key 的那个节点”（无视其 cnt，整节点移除）
// 用于两子节点场景下的节点替换后，删除继承来源节点，保持“每个键仅一个节点”的不变式
void eraseAll(Node*& node, int key) {
    if (!node) return;
    if (key < node->key) {
        eraseAll(node->left, key);
    } else if (key > node->key) {
        eraseAll(node->right, key);
    } else {
        if (!node->left && !node->right) { // 叶子节点
            delete node;
            node = nullptr;
        } else if (!node->left) { // 仅有右子节点
            Node* tmp = node;
            node = node->right;
            delete tmp;
        } else if (!node->right) { // 仅有左子节点
            Node* tmp = node;
            node = node->left;
            delete tmp;
        } else {
            // 找到右子树中的最小节点作为后继，拷贝其 key 与 cnt，上移后再在右子树中删除该节点
            Node* s = node->right;
            while (s->left) s = s->left;
            node->key = s->key;
            node->cnt = s->cnt;
            eraseAll(node->right, s->key);
        }
    }
    updateSize(node);
}

void erase(Node*& node, int key) {
    if (!node) return;
    if (key < node->key) {
        erase(node->left, key);
    } else if (key > node->key) {
        erase(node->right, key);
    } else {
        if (node->cnt > 1) {
            node->cnt--; // 同值多次出现，删一份
        } else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
                return;
            } else if (!node->left) {
                Node* tmp = node;
                node = node->right;
                delete tmp;
            } else if (!node->right) {
                Node* tmp = node;
                node = node->left;
                delete tmp;
            } else {
                // 两子节点：用右子树最小节点（后继）替换当前节点
                Node* s = node->right;
                while (s->left) s = s->left;
                node->key = s->key;
                node->cnt = s->cnt;      // 吸收后继节点的全部计数，保持“每个键仅一个节点”
                eraseAll(node->right, s->key); // 右子树中移除该后继节点
            }
        }
    }
    updateSize(node);
}

int rankLess(Node* node, int key) {
    if (!node) return 0;
    if (key < node->key) {
        return rankLess(node->left, key);
    }
    if (key == node->key) {
        return nodeSize(node->left);
    }
    return nodeSize(node->left) + node->cnt + rankLess(node->right, key);
}

int kth(Node* node, int k) {
    while (node) {
        int leftSize = nodeSize(node->left);
        if (k <= leftSize) {
            node = node->left;
        } else if (k <= leftSize + node->cnt) {
            return node->key;
        } else {
            k -= leftSize + node->cnt;
            node = node->right;
        }
    }
    return -1; // 不存在
}
// the predecessor is the largest number strictly smaller than key
int predecessor(Node* node, int key) {
    int res = std::numeric_limits<int>::min();
    while (node) {
        if (key <= node->key) {
            node = node->left;
        } else {
            res = node->key;
            node = node->right;
        }
    }
    return res;
}
// the successor is the smallest number strictly larger than key
int successor(Node* node, int key) {
    int res = std::numeric_limits<int>::max();
    while (node) {
        if (key >= node->key) {
            node = node->right;
        } else {
            res = node->key;
            node = node->left;
        }
    }
    return res;
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
            insert(root, x);
        } else if (op == 2) {
            erase(root, x);
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
    return 0;
}