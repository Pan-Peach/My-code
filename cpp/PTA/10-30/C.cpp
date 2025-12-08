#include<bits/stdc++.h>
using namespace std;

class BinaryTree {
    private:
        struct Node {
            char data;
            Node* left;
            Node* right;
            Node(char val) : data(val), left(nullptr), right(nullptr) {}
        };

    public:
        void preorder(Node* node) {
            if (!node) return;
            cout << node->data;
            preorder(node->left);
            preorder(node->right);
        }

        Node* root;
        BinaryTree() : root(nullptr) {}

        bool buildByInAndPostorder(Node*& node, string& inorder, string& postorder){
            if(inorder.length() != postorder.length()){
                cout<<"INVALID"<<endl;
                return false;
            }
            if(inorder.empty() || postorder.empty()) {
                node = nullptr;
                return true;
            }
            char root = postorder.back();
            Node* newNode = new Node(postorder.back());
            node = newNode;
            postorder.pop_back();
            int pos = inorder.find(root);
            if(pos == string::npos){
                cout<<"INVALID"<<endl;
                return false;
            }
            string leftin = inorder.substr(0, pos);
            string rightin = inorder.substr(pos + 1);
            string rightpost = postorder.substr(leftin.length());
            string leftpost = postorder.substr(0, leftin.length());
            if(!buildByInAndPostorder(node->right, rightin, rightpost)){
                return false;
            }
            if(!buildByInAndPostorder(node->left, leftin, leftpost)){
                return false;
            }
            return true;
        }

        int getHeight(Node* node){
            if(!node) return 0;
            return max(getHeight(node->left), getHeight(node->right)) + 1;
        }
};

int main(){
    string inorder, postorder;
    while(getline(cin, postorder)){
        getline(cin, inorder);
        BinaryTree tree;
        if(!tree.buildByInAndPostorder(tree.root, inorder, postorder)){
            continue;
        }
        cout << tree.getHeight(tree.root)-1 << endl;
        tree.preorder(tree.root);
        cout << endl;
        
    }
    return 0;
}