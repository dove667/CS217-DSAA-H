#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

struct Node {
    string val;
    int truth_val = 0;
    int sense_val = 0;
    Node *left = nullptr, *right = nullptr;
    explicit Node(string v) : val(std::move(v)) {}
};

static Node* buildTree(const vector<string>& rpn) {
    stack<Node*> st;
    auto isOp = [](const string& t) {
        return t == "!" || t == "&" || t == "|";
    };
    for (auto &tok : rpn) {
        if (!isOp(tok)) st.push(new Node(tok));
        else {
            Node* n = new Node(tok);
            if (tok == "!") {
                n->right = st.top(); st.pop();
            } else {
                n->right = st.top(); st.pop();
                n->left = st.top(); st.pop();
            }
            st.push(n);
        }
    }
    return st.top();
}

static void substituteVars(Node* node, const vector<int>& values) {
    if (!node) return;
    if (!node->left && !node->right) {
        if (node->val[0] == 'x') {
            int idx = stoi(node->val.substr(1)) - 1;
            node->truth_val = values[idx];
        }
        return;
    }
    substituteVars(node->left, values);
    substituteVars(node->right, values);
}

//子底向上评估
static int evaluate(Node* node, const vector<int>& values) {
    if (!node->left && !node->right) { // 叶子节点
        int idx = stoi(node->val.substr(1)) - 1;
        node->truth_val = values[idx];
        return node->truth_val;
    }
    if (node->val == "!") {
        node->truth_val = !evaluate(node->right, values);
    } else if (node->val == "&") {
        int l = evaluate(node->left, values);
        int r = evaluate(node->right, values);
        node->truth_val = l & r;
    } else if (node->val == "|") {
        int l = evaluate(node->left, values);
        int r = evaluate(node->right, values);
        node->truth_val = l | r;
    }
    return node->truth_val;
}

// 自顶向下传播
static void propagate(Node* node) {
    if (!node) return;
    if (node->val == "!" && node->right) { // ！子节点的敏感性与！相同
        node->right->sense_val = node->sense_val;
        propagate(node->right);
    } else if (node->val == "&" && node->left && node->right) { // 只有&敏感而且子节点一个为真时另一个子节点敏感
        node->left->sense_val = node->sense_val && (node->right->truth_val == 1);
        propagate(node->left);
        node->right->sense_val = node->sense_val && (node->left->truth_val == 1);
        propagate(node->right);
    } else if (node->val == "|" && node->left && node->right) { // 只有|敏感而且子节点一个为假时另一个子节点敏感
        node->left->sense_val = node->sense_val && (node->right->truth_val == 0);
        propagate(node->left);
        node->right->sense_val = node->sense_val && (node->left->truth_val == 0);
        propagate(node->right);
    }
}

static void collectSens(Node* node, vector<int>& sensitive) {
    if (!node) return;
    if (!node->left && !node->right && node->val[0] == 'x') {
        int idx = stoi(node->val.substr(1)) - 1;
        if (idx >= 0 && idx < (int)sensitive.size())
            sensitive[idx] = node->sense_val;
        return;
    }
    collectSens(node->left, sensitive);
    collectSens(node->right, sensitive);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> tokens;
    string line;
    if (!getline(cin, line)) return 0;
    istringstream iss(line);
    string tok;
    while (iss >> tok) tokens.push_back(tok);

    Node* root = buildTree(tokens);

    int n;
    cin >> n;
    vector<int> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];

    evaluate(root, values);
    root->sense_val = 1;
    propagate(root);

    vector<int> sensitive(n, 0);
    collectSens(root, sensitive);

    int q; cin >> q;
    while (q--) {
        int i; cin >> i; --i;
        cout << (sensitive[i] ? !root->truth_val : root->truth_val) << "\n";
    }
}
