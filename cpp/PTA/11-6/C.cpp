#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1500;

int Treesize=0;

class DSU{
    private:
        vector<int> parent;
    public:
        DSU(int n){
            parent.resize(n+1);
            for(int i=0;i<=n;i++){
                parent[i] = i;
            }
        }

        int find(int x){
            if(parent[x] != x){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void merge(int x, int y){
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY){
                parent[rootY] = rootX;
            }
        }
        
};

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* fa; // Parent pointer

    Node(int val) : data(val), left(nullptr), right(nullptr), fa(nullptr) {}
};

struct PathLCA{
    int a,b,lca;
    PathLCA(int _a=0, int _b=0, int _lca=0) : a(_a), b(_b), lca(_lca) {}
    
};

Node* root = nullptr;
map<int, Node*> node_map;

Node* buildByPreorder(queue<int>& preorder, Node* parent){
    if(preorder.empty()) return nullptr;
    int val = preorder.front();
    preorder.pop();
    if(val == 0) {
        return nullptr;
    }
    Node* node = new Node(val);
    node->fa = parent;
    node_map[val] = node;
    node->left = buildByPreorder(preorder, node);
    node->right = buildByPreorder(preorder, node);
    Treesize++;
    return node;
}

void findPaPath(Node* ch, Node* pa, vector<Node*>& path){
    path.push_back(ch);
    Node* cur=ch->fa;
    while(cur){
        path.push_back(cur);
        if(cur==pa) break;
        cur=cur->fa;
    }
    return;
}

vector<Node*> getPath(int a,int b,int lca){
    vector<Node*> left,right,path;
    Node* A=node_map[a], *B=node_map[b], *L=node_map[lca];
    findPaPath(A,L,left);
    findPaPath(B,L,right);
    left.pop_back();
    path=left;
    reverse(right.begin(), right.end());
    path.insert(path.end(), right.begin(), right.end());
    return path;
}

void Tarjan(Node* node, DSU& dsu, vector<bool>& visited, vector<pair<int,int>>& query, vector<PathLCA>& results) {
    if(!node) return;
    int u = node->data;
    visited[u] = true;
    if(node->left) {
        Tarjan(node->left, dsu, visited, query, results);
        dsu.merge(u, node->left->data);
    }
    if(node->right) {
        Tarjan(node->right, dsu, visited, query, results);
        dsu.merge(u, node->right->data);
    }
    for(int i=0;i<query.size();i++){
        int v = query[i].first;
        int idx = query[i].second;
        if(v&&visited[v]){
            results[idx] = PathLCA(u,v,dsu.find(u));
        }
    }
    return;
}

vector<Node*> getPathSimple(int a,int b){
    Node* A=node_map[a], *B=node_map[b];
    vector<Node*> left,right,path;
    
    Node* curleft = A;
    Node* curright = B;
    Node* postright = B;
    while(curleft){
        bool islca=0;
        left.push_back(curleft);
        while(curright){
            right.push_back(curright);
            if(curright==curleft){
                islca=1;
                break;
            }
            else{
                curright=curright->fa;
            }
        }
        if(islca) break;
        else{
            right.clear();
            curright=B;
            curleft=curleft->fa;
        }
    }
    left.pop_back();
    path=left;
    reverse(right.begin(), right.end());
    path.insert(path.end(), right.begin(), right.end());
    return path;
}

int main(){
    string s;
    getline(cin, s);
    stringstream ss(s);
    int num;
    queue<int> preorder;
    // map<int,int> ask;
    // map<int, pair<int,int>> query;
    // vector<PathLCA> results;
    // vector<bool> visited(Treesize+1, false);
    // DSU dsu(Treesize);
    while(ss >> num){
        preorder.push(num);
    }
    root = buildByPreorder(preorder, nullptr);
    int m;
    cin >> m;
    int maxNode = node_map.rbegin()->first;
    // results.resize(maxNode+1);
    // int a,b;
    // for(int i=0;i<m;i++){
    //     cin>>a>>b;
    //     if(a==b) results[i] = a;
    //     else{
    //         query[a] = {b,i};
    //         query[b] = {a,i};
    //     }
    // }
    //Tarjan(root, dsu, visited, query, results);
    

    for(int i=0;i<m;i++){
        // PathLCA curPath = results[i];
        int a,b;
        cin>>a>>b;
        vector<Node*> path = getPathSimple(a,b);
        cout<<path.size()-1<<endl;
        for(int i=0;i<path.size();i++){
            cout<<path[i]->data<<" ";
        }
        cout<<endl;
    }

    return 0;
}