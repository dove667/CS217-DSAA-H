#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * AVL 树节点定义
 * 我们在每个节点存储高度 (height)，以便快速计算平衡因子
 */
struct Node {
    int key;
    int height;
    Node *left;
    Node *right;

    Node(int v) : key(v), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    Node* root = nullptr;
    int rotationCount = 0;  // 统计旋转次数
    bool enableDebug = false;

    // 获取节点高度，空节点高度为 0
    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    // 计算平衡因子：左子树高度 - 右子树高度
    int getBalanceFactor(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    // 更新节点高度：1 + max(左高度, 右高度)
    void updateHeight(Node* n) {
        if (n) {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }

    /**
     * 右旋转 (Right Rotation) - 用于处理 LL 情况 
     * 想象把中间的节点“提”上来，原来的父节点下沉到右边
     */
    Node* rightRotate(Node* y) {        rotationCount++;
        if (enableDebug) cout << "  → 右旋 (节点 " << y->key << ")\n";        Node* x = y->left;
        Node* T2 = x->right;

        // 执行旋转
        x->right = y;
        y->left = T2;

        // 更新受影响的高度
        updateHeight(y);
        updateHeight(x);

        return x; // 返回新的根
    }

    /**
     * 左旋转 (Left Rotation) - 用于处理 RR 情况
     */
    Node* leftRotate(Node* x) {
        rotationCount++;
        if (enableDebug) cout << "  → 左旋 (节点 " << x->key << ")\n";
        Node* y = x->right;
        Node* T2 = y->left;

        // 执行旋转
        y->left = x;
        x->right = T2;

        // 更新高度
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    /**
     * 递归插入
     * 时间复杂度: O(log n)
     */
    Node* insert(Node* node, int key) {
        // 1. 执行标准的 BST 插入
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // 不允许重复键

        // 2. 更新当前节点高度
        updateHeight(node);

        // 3. 获取平衡因子，判断是否失衡
        int balance = getBalanceFactor(node);

        // --- 重新平衡的四种情况 ---

        // Case LL: 左左失衡 -> 右旋
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Case RR: 右右失衡 -> 左旋 
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Case LR: 左右失衡 -> 先左旋子节点，再右旋自己
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Case RL: 右左失衡 -> 先右旋子节点，再左旋自己 
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // 中序遍历，验证 BST 属性（应为升序）
    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " (h=" << root->height << ") ";
            inorder(root->right);
        }
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    Node* erase(Node* root, int key) {
        if (!root) return root;

        if (key < root->key) {
            root->left = erase(root->left, key);
        } else if (key > root->key) {
            root->right = erase(root->right, key);
        } else {
            if (!root->left || !root->right) {
                Node* child = root->left ? root->left : root->right;
                if (!child) {
                    child = root;
                    root = nullptr;
                } else {
                    *root = *child; // 拷贝子节点内容
                }
                delete child;
            } else {
                Node* successor = minValueNode(root->right);
                root->key = successor->key;
                root->right = erase(root->right, successor->key);
            }
        }

        if (!root) return root;

        updateHeight(root);
        int balance = getBalanceFactor(root);

        // LL
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rightRotate(root);

        // LR
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // RR
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return leftRotate(root);

        // RL
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
};

/**
 * 测试案例
 */
int main() {
    AVLTree tree;
    tree.enableDebug = true;
    
    /* 构造一个需要多次旋转的序列：10, 20, 30, 40, 50, 25 */
    vector<int> keys = {10, 20, 30, 40, 50, 25};
    
    cout << "========== 插入操作 ==========\n";
    cout << "依次插入节点: ";
    for (int k : keys) {
        cout << k << " ";
    }
    cout << "\n\n";

    for (int k : keys) {
        cout << "插入 " << k << "\n";
        tree.rotationCount = 0;
        tree.root = tree.insert(tree.root, k);
        cout << "  旋转次数: " << tree.rotationCount << "\n";
    }

    cout << "\nAVL 树中序遍历结果 (验证排序及高度):" << endl;
    tree.inorder(tree.root);
    
    cout << "\n\n根节点是: " << tree.root->key << "，高度为: " << tree.root->height << endl;

    vector<int> removeKeys = {40, 20, 30, 10};
    cout << "\n========== 删除操作 ==========\n";
    cout << "依次删除节点: ";
    for (int k : removeKeys) {
        cout << k << " ";
    }
    cout << "\n\n";

    for (int k : removeKeys) {
        cout << "删除 " << k << "\n";
        tree.rotationCount = 0;
        tree.root = tree.erase(tree.root, k);
        cout << "  旋转次数: " << tree.rotationCount << "\n";
    }

    cout << "\n删除后中序遍历: " << endl;
    tree.inorder(tree.root);
    if (tree.root) {
        cout << "\n\n删除后根节点是: " << tree.root->key << "，高度为: " << tree.root->height << endl;
    } else {
        cout << "\n\n树已为空" << endl;
    }

    return 0;
}