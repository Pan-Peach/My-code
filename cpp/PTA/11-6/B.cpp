#include<bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* fa; // Parent pointer

    Node(int val) : data(val), left(nullptr), right(nullptr), fa(nullptr) {}
};

Node* root = nullptr;

Node* buildByPreorder(queue<int>& preorder, Node* parent){
    if(preorder.empty()) return nullptr;
    int val = preorder.front();
    preorder.pop();
    if(val == 0) {
        return nullptr;
    }
    Node* node = new Node(val);
    node->fa = parent;
    node->left = buildByPreorder(preorder, node);
    node->right = buildByPreorder(preorder, node);
    return node;
}

void dfs(Node* node, list<list<Node*>>& path, int sum, int target, list<Node*>& currentPath, int& count) {
    if(!node) return;
    if(!node->left && !node->right) {
        sum += node->data;
        currentPath.push_back(node);
        if(sum == target) {
            count++;
            path.push_back(currentPath);
        }
        currentPath.pop_back();
        return;
    }
    sum += node->data;
    currentPath.push_back(node);
    dfs(node->left, path, sum, target, currentPath, count);
    dfs(node->right, path, sum, target, currentPath, count);
    currentPath.pop_back();
    return;
}

int main(){
    string s;
    getline(cin, s);
    stringstream ss(s);
    int num;
    queue<int> preorder;
    while(ss >> num){
        preorder.push(num);
    }
    root = buildByPreorder(preorder, nullptr);
    int target;
    cin >> target;
    list<list<Node*>> paths;
    list<Node*> currentPath;
    int count = 0;
    dfs(root, paths, 0, target, currentPath, count);
    cout << count << endl;
    for(const auto& path : paths){
        for(const auto& node : path){
            cout << node->data << " ";
        }
        cout << endl;
    }
    return 0;
}