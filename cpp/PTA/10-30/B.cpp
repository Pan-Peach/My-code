#include<bits/stdc++.h>
using namespace std;
const int MAXN = 160000;


class BinaryTree {
    private:
        struct Node {
            int data;
            int left;
            int right;
            int pa;
            Node(int val) : data(val), left(-1), right(-1), pa(-1) {}
            Node() : data(0), left(-1), right(-1), pa(-1) {}
        };
        Node nodes[MAXN];
        int poolIdx = 1;
        void newNode(int val){
            nodes[poolIdx] = Node(val);
            poolIdx++;
        }

    public:
        int root=0;
        BinaryTree() {}

        void buildByPreorder(int idx, queue<int>& preorder){
            if(preorder.empty()) return;
            int val = preorder.front();
            preorder.pop();
            if(val == 0) return;
            else{
                nodes[idx].data = val;
                newNode(0);
                nodes[idx].left = poolIdx - 1;
                nodes[poolIdx - 1].pa = idx;
                buildByPreorder(nodes[idx].left, preorder);
                newNode(0);
                nodes[idx].right = poolIdx - 1;
                nodes[poolIdx - 1].pa = idx;
                buildByPreorder(nodes[idx].right, preorder);
            }
        }

        void preorder(int idx){
            if(idx == -1) return;
            cout << nodes[idx].data << " ";
            preorder(nodes[idx].left);
            preorder(nodes[idx].right);
        }

        bool query(int idx, int val){
            if(idx==-1) return false;
            if(nodes[idx].data == val){
                if(nodes[idx].pa == -1) cout<<0<<endl;
                else cout<<nodes[nodes[idx].pa].data<<endl;
                return true;
            }
            return query(nodes[idx].left, val)
            || query(nodes[idx].right, val);
        }   

};


int main(){
    string line;
    getline(cin, line);
    queue<int> preorder;
    for(int i = 0; i < line.size(); ){
        while(i < line.size() && line[i] == ' ') i++;
        if(i >= line.size()) break;
        int j = i;
        while(j < line.size() && line[j] != ' ') j++;
        int val = stoi(line.substr(i, j - i));
        preorder.push(val);
        i = j;
    }
    BinaryTree tree;
    tree.buildByPreorder(tree.root, preorder);
    int m,k;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> k;
        if(!tree.query(tree.root, k)) cout<<0<<endl;
    }
    return 0;
}