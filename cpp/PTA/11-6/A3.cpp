#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <map>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* fa; // Parent pointer

    Node(int val) : data(val), left(nullptr), right(nullptr), fa(nullptr) {}
};

Node* root = nullptr;
std::map<int, Node*> node_map;

void delete_subtree(Node* node) {
    if (!node) {
        return;
    }
    delete_subtree(node->left);
    delete_subtree(node->right);
    node_map.erase(node->data);
    delete node;
}

Node* build_tree(std::queue<int>& q, Node* parent) {
    if (q.empty() || q.front() == 0) {
        q.pop();
        return nullptr;
    }

    int val = q.front();
    q.pop();
    Node* current_node = new Node(val);
    current_node->fa = parent;
    node_map[val] = current_node;
    current_node->left = build_tree(q, current_node);
    current_node->right = build_tree(q, current_node);

    return current_node;
}

void inorder_traversal(Node* node) {
    if (!node) {
        return;
    }
    inorder_traversal(node->left);
    std::cout << node->data << " ";
    inorder_traversal(node->right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int num;
    std::queue<int> preorder_sequence;
    while (ss >> num) {
        preorder_sequence.push(num);
    }

    root = build_tree(preorder_sequence, nullptr);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int k;
        std::cin >> k;

        if (node_map.count(k) == 0) {
            std::cout << 0 << "\n";
        } else {
            Node* target_node = node_map[k];
            Node* parent = target_node->fa;

            if (parent != nullptr) {
                if (parent->left == target_node) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }

            delete_subtree(target_node);

            inorder_traversal(root);
            std::cout << "\n";
        }
    }

    return 0;
}


