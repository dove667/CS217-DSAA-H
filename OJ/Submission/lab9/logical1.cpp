#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cctype>
using namespace std;

struct Node {
    string val;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(string  v) : val(std::move(v)) {}
};

static string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static vector<string> tokenize(const string& s) {
    vector<string> out;
    for (size_t i = 0; i < s.size();) {
        if (isspace(static_cast<unsigned char>(s[i]))) { ++i; continue; }
        if (s[i] == '0' || s[i] == '1') {
            out.emplace_back(1, s[i]);
            ++i;
        } else {
            if (i + 2 <= s.size() && s.substr(i, 2) == "->") {
                out.emplace_back("->");
                i += 2;
            } else {
                string t(1, s[i]);
                out.push_back(t);
                ++i;
            }
        }
    }
    return out;
}

static vector<string> toRPN(const vector<string>& tokens) {
    vector<string> out;
    stack<string> ops;

    unordered_map<string,int> prec = {
        {"->", 1},
        {"|", 2},
        {"^", 3},
        {"&", 4},
        {"!", 5}
    };
    unordered_map<string,bool> rightAssoc = {
        {"->", true}, {"!", true}
    };

    auto isOp = [&](const string& t){ return prec.find(t) != prec.end(); };

    for (const auto & tok : tokens) {
        if (tok.empty()) continue;
        if (tok == "(") {
            ops.push(tok);
        } else if (tok == ")") {
            while (!ops.empty() && ops.top() != "(") {
                out.push_back(ops.top()); ops.pop();
            }
            if (!ops.empty() && ops.top() == "(") ops.pop();
        } else if (isOp(tok)) {
            while (!ops.empty() && isOp(ops.top())) {
                string o2 = ops.top();
                if ((!rightAssoc[tok] && prec[tok] <= prec[o2]) ||
                    ( rightAssoc[tok] && prec[tok] <  prec[o2])) {
                    out.push_back(o2); ops.pop();
                } else break;
            }
            ops.push(tok);
        } else {
            out.push_back(tok);
        }
    }
    while (!ops.empty()) { out.push_back(ops.top()); ops.pop(); }
    return out;
}

static Node* buildTreeFromRPN(const vector<string>& rpn) {
    stack<Node*> st;
    auto isOp = [](const string& t){
        return t == "!" || t == "&" || t == "|" || t == "^" || t == "->";
    };
    for (const auto &tok : rpn) {
        if (!isOp(tok)) {
            st.push(new Node(tok));
        } else {
            if (tok == "!") {
                if (st.empty()) return nullptr;
                Node* a = st.top(); st.pop();
                Node* n = new Node(tok);
                n->right = a;
                st.push(n);
            } else {
                if (st.size() < 2) return nullptr;
                Node* r = st.top(); st.pop();
                Node* l = st.top(); st.pop();
                Node* n = new Node(tok);
                n->left = l;
                n->right = r;
                st.push(n);
            }
        }
    }
    if (st.empty()) return nullptr;
    Node* root = st.top(); st.pop();
    return root;
}

static bool evaluate(const Node* node) {
    if (!node) return false;
    // 叶子节点：'0' 或 '1'
    if (!node->left && !node->right) {
        if (node->val == "1") return true;
        return false; // 包含 '0' 或其它视为 false
    }
    if (node->val == "!") {
        return !evaluate(node->right);
    }
    bool L = evaluate(node->left);
    bool R = evaluate(node->right);
    if (node->val == "&") return L && R;
    if (node->val == "|") return L || R;
    if (node->val == "^") return L ^ R;
    if (node->val == "->") return (!L) || R;
    return false;
}

static void deleteTree(Node* n) {
    if (!n) return;
    deleteTree(n->left);
    deleteTree(n->right);
    delete n;
}

int main() {
    int T;
    if (!(cin >> T)) return 0;
    string line;
    getline(cin, line);
    for (int i = 0; i < T; ++i) {
        if (!getline(cin, line)) break;
        line = trim(line);
        if (line.empty()) { --i; continue; }

        auto tokens = tokenize(line); // 解析表达式
        auto rpn = toRPN(tokens); // 中缀转后缀
        Node* root = buildTreeFromRPN(rpn); // 构建表达式树
        if (!root) {
            cout << "解析失败\n";
        } else {
            bool res = evaluate(root);
            cout << (res ? '1' : '0') << "\n";
            deleteTree(root);
        }
    }
    return 0;
}