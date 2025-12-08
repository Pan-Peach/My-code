#include<bits/stdc++.h>
using namespace std;

class BinaryTree {
    private:
        struct Node {
            int data;
            Node* left;
            Node* right;
            int fa;
            Node(int val) : data(val), left(nullptr), right(nullptr) {}
        };

        void inorder(Node* node) {
            if (!node) return;
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }

        void preorder(Node* node) {
            if (!node) return;
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }

        void postorder(Node* node) {
            if (!node) return;
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }

        public:
        Node* root;
        BinaryTree() : root(nullptr) {}
    
        void buildByPreorder(Node*& node, queue<int>& preorder, int fa) {
            if(preorder.empty()) return;
            int val = preorder.front();
            preorder.pop();
            if(val == 0) {
                node = nullptr;
                return;
            }else{
                node = new Node(val);
                node->fa = fa;
                buildByPreorder(node->left, preorder, val);
                buildByPreorder(node->right, preorder, val);
            }
            
        }

        void outputorders(){
            preorder(root);
            cout << endl;
            inorder(root);
            cout << endl;
            postorder(root);
            cout << endl;
        }

        bool query(Node* node, int k){
            if(!node) return false;
            if(node->data == k){
                if(node->fa == 0) cout << 0 << endl;
                else cout << node->fa << endl;
                return true;
            }
            bool left = query(node->left, k);
            if(left) return true;
            bool right = query(node->right, k);
            return right;
        }
};


int main() {
    string s;
    queue<int> preorder;
    getline(cin, s);
    for(size_t i = 0; i < s.size(); ) {
        while (i < s.size() && s[i] == ' ') i++;
        if (i >= s.size()) break;
        int num = 0;
        while (i < s.size() && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            i++;
        }
        preorder.push(num);
    }

    BinaryTree tree;
    tree.buildByPreorder(tree.root, preorder, 0);
    int m,k;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> k;
        bool ans = tree.query(tree.root, k);
        if(!ans) cout << 0 << endl;
    }
    return 0;
}