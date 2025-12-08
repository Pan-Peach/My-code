#include<bits/stdc++.h>
using namespace std;

class BinaryTree{
    private:
    class Node{
        public:
        char val;
        Node *left,*right;
        Node(char v):val(v),left(nullptr),right(nullptr){}
    };
    public:
    Node* root;
    public:
    BinaryTree(){
        root=new Node('0');
    }

    void Preorder(Node* node){

    }

    void Inorder(Node* node){

    }

    void Backorder(Node* node){
        // if(node->left==nullptr&&node->right==nullptr){
        //     // cout<<node->val;
        //     return;
        // }
        if(node->left) Backorder(node->left);
        if(node->right) Backorder(node->right);
        cout<<node->val;

    }

    

    Node* BuildBackorder(string a,string b, Node* node ){
        if(a.size()==0) return nullptr;
        char root=b[0];
        if(node) node->val=root;
        else node=new Node(root);
        int pos=a.find(root);
        node->left = BuildBackorder(a.substr(0,pos),b.substr(1,pos),node->left);
        node->right = BuildBackorder(a.substr(pos+1),b.substr(pos+1),node->right);
        return node;
    }
};

int main(){
    string a,b;
    cin>>a>>b;
    BinaryTree tree;
    tree.BuildBackorder(a,b,tree.root);
    tree.Backorder(tree.root);
    return 0;
}