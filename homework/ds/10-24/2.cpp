#include<bits/stdc++.h>
using namespace std;

class BinaryTree{
    private:
        class Node{
            public:
                int data;
                Node *left;
                Node *right;
                Node(int val){
                    data = val;
                    left = nullptr;
                    right = nullptr;
                }
        };
        Node *root;

    public:
        BinaryTree(){
            root = nullptr;
        }

        bool isComplete(){
            if(!root) return true;
            queue<Node*> q;
            q.push(root);
            bool end = false;
            while(!q.empty()){
                Node *curr = q.front();
                q.pop();
                if(curr==nullptr){
                    end = true;
                }
                else{
                    if(end) return false;
                    q.push(curr->left);
                    q.push(curr->right);
                }
            }
            return true;
        }

        int getHeightAndPath(Node *node, vector<int> &path){
            if(!node) return 0;
            path.push_back(node->data);
            int leftHeight = getHeightAndPath(node->left,path);
            int rightHeight = getHeightAndPath(node->right,path);

            if(leftHeight>=rightHeight){
                if(node->right) path.pop_back();
                return leftHeight + 1;
            }else{
                if(node->left) path.pop_back();
                return rightHeight + 1;
            }
        }

        bool isSimilar(Node* n1,Node* n2){
            if(!n1 && !n2) return true;
            if(!n1 || !n2) return false;
            return isSimilar(n1->left,n2->left) && isSimilar(n1->right,n2->right);

        }
};