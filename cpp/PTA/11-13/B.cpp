#include<bits/stdc++.h>
using namespace std;

class BTree{
public:
    struct Node{
        char val;
        Node* l; Node* r;
        Node(char val): val(val),l(nullptr),r(nullptr){}
        Node(): val('#'),l(nullptr),r(nullptr){}
    };

    struct Levelinfo{
        Node* node=nullptr;
        int level=0;
        Levelinfo(Node* node, int level): node(node),level(level){}
    };

    Node* root=nullptr;

    Node* BuildByPreorder(queue<char>& preorder){
        if(preorder.empty()) return nullptr;
        char cur = preorder.front();
        Node* node;
        preorder.pop();
        if(cur=='#') return nullptr;
        else{
            node= new Node(cur);
            node->l = BuildByPreorder(preorder);
            node->r = BuildByPreorder(preorder);
        }
        return node;
    }

    void preorder(Node* node){
        if(node==nullptr) return;
        char cur=node->val;
        cout<<cur<<' ';
        preorder(node->l);
        preorder(node->r);
        return;
    }

    void levelorder(){
        
        queue<Levelinfo> q;
        vector<int> levelcount(100,0);
        q.push(Levelinfo(root,0));
        int totlevel=0;
        while(!q.empty()){
            Node* cur=q.front().node;
            int level = q.front().level;
            q.pop();
            int outdegree=0;
            if(cur->l) outdegree++;
            if(cur->r) outdegree++;
            if(outdegree==1) levelcount[level]++;
            if(cur->l) q.push(Levelinfo(cur->l,level+1));
            if(cur->r) q.push(Levelinfo(cur->r,level+1));
            if(cur->l || cur->r) totlevel=max(totlevel,level+1);
        }
        for(int i=0;i<=totlevel;i++){
            cout<<levelcount[i]<<endl;
        }
        return;
    }

};

int main(){
    string s;
    getline(cin, s);
    stringstream ss(s);
    char num;
    queue<char> preorder;
    while(ss >> num){
        preorder.push(num);
    }
    BTree bt;
    bt.root = bt.BuildByPreorder(preorder);
//    bt.preorder(bt.root);
    bt.levelorder();
    return 0;
}