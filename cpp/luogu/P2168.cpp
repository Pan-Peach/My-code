// #include<bits/stdc++.h>
// using namespace std;
// const long long maxn=1e5+10;

// class Huffman{
//     private:
//         class Node{
//             public:
//                 long long val;
//                 long long level=0;
//                 vector<Node*> child;
//                 Node(long long v):val(v){}

//                 void addChild(Node* c){
//                     c->level=level+1;
//                     child.push_back(c);
//                 }

//                 long long getChildNum(){
//                     return child.size();
//                 }

//                 bool operator <(const Node& other) const{
//                     return val>other.val;
//                 }
//         };
        
//         class cmp{
//             public:
//                 bool operator()(Node* a, Node* b){
//                     return a->val>b->val;
//                 }
//         };

//         long long numChild;
//         Node* root;
//         priority_queue<Node*,vector<Node*>,cmp> pq;
//         vector<long long> weight;

//     public:
//         Huffman(long long n, long long m){
//             weight.resize(m+1);
//             for(long long i=1;i<=m;i++){
//                 long long w;
//                 scanf("%lld",&w);
//                 pq.push(new Node(w));
//                 weight[i]=w;
//             }
//             numChild=n;
            
//             build();
//         }

//         void build(){
//             while ((pq.size() - 1) % (numChild - 1) != 0) {
//                 Node* zero = new Node(0);
//                 zero->val = 0;
//                 pq.push(zero);
//             }
//            while(pq.size()>1){
//                 Node* cur=new Node(0);
//                 long long w=0;
//                 for(long long i=0;i<numChild;i++){
//                     if(pq.empty()) break;
//                     Node* c=pq.top(); pq.pop();
//                     w+=c->val;
//                     cur->addChild(c);
//                 }
//                 cur->val=w;
//                 pq.push(cur);
//             }
//             root=pq.top(); pq.pop();
//             updateLevel(root);
//         }
    
//         void updateLevel(Node* cur){
//             if(cur==nullptr) return;
//             for(auto c:cur->child){
//                 c->level=cur->level+1;
//                 updateLevel(c);
//             }
//         }

//         long long getHeight(Node* cur){
//             if(cur==nullptr) return 0;
//             long long h=0;
//             for(auto c:cur->child){
//                 h=max(h,getHeight(c));
//             }
//             return h+1;
//         }

//         void levelOrder(){
//             queue<Node*> q;
//             q.push(root);
//             long long level=0;
//             long long size=1;
//             long long minLen=0;
//             long long maxHeight=getHeight(root)-1;
//             while(!q.empty()){
//                 Node* cur=q.front(); q.pop();
//                 level = cur->level;
//                 if(cur->getChildNum()==0)       
//                 minLen+=level*cur->val;
//                 for(auto c:cur->child){
//                     q.push(c);
//                     size++;
//                 }
//             }
//             printf("%lld\n%lld\n",minLen,maxHeight);
//         }

    
// };
// int main(){
//     long long n,m;
//     scanf("%lld%lld",&n,&m);
//     Huffman h(m,n);
//     h.levelOrder();
//     return 0;
// }

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

struct Node {
    ll w;   // 权值
    ll h;   // 高度
    Node(ll w_, ll h_) : w(w_), h(h_) {}
    bool operator<(const Node& other) const {
        if (w != other.w) return w > other.w; // 权值小优先
        return h > other.h; // 权值相同时高度小优先
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    priority_queue<Node> pq;
    
    for (int i = 0; i < n; i++) {
        ll w;
        cin >> w;
        pq.emplace(w, 0);
    }
    
    // 补 0 节点
    while ((pq.size() - 1) % (k - 1) != 0) {
        pq.emplace(0, 0);
    }
    
    ll ans_len = 0;
    
    while (pq.size() > 1) {
        ll sum_w = 0;
        ll max_h = 0;
        
        for (int i = 0; i < k; i++) {
            Node node = pq.top();
            pq.pop();
            sum_w += node.w;
            max_h = max(max_h, node.h);
        }
        
        ans_len += sum_w;
        pq.emplace(sum_w, max_h + 1);
    }
    
    cout << ans_len << "\n";
    cout << pq.top().h << "\n";
    
    return 0;
}