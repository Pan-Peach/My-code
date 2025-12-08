#include<bits/stdc++.h>
using namespace std;

class BinaryTree{
    private:
        vector<int> tree;
        int index;
    public:
        BinaryTree(int size){
            tree.resize(size+1, -1);
            for(int i=1;i<=size;i++) tree[i] = i;
            index = 1;
        }

        void preOrder(int root, vector<int> &res){
            if(root>=tree.size() || tree[root]==-1) return;
            res.push_back(tree[root]);
            preOrder(2*root,res);
            preOrder(2*root+1,res);
        }

        void inOrder(int root, vector<int> &res){
            if(root>=tree.size() || tree[root]==-1) return;
            inOrder(2*root,res);
            res.push_back(tree[root]);
            inOrder(2*root+1,res);
        }

        void postOrder(int root, vector<int> &res){
            if(root>=tree.size() || tree[root]==-1) return;
            postOrder(2*root,res);
            postOrder(2*root+1,res);
            res.push_back(tree[root]);
        }

};

int main(){
    BinaryTree bt(400);
    vector<int> pre,res,in,post;
    pre.push_back(-1);
    in.push_back(-1);
    post.push_back(-1);
    bt.preOrder(1,pre);
    bt.inOrder(1,in);
    bt.postOrder(1,post);
    cout<<"Preorder: "<<pre[100];
    cout<<"\nInorder: "<<in[100];
    cout<<"\nPostorder: "<<post[100];
    return 0;
}

